#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "activation.h"
#include "layer.h"

typedef struct dense_network {
    uint32_t layer_count;
    uint32_t *layer_units;
    activation *funcs;
    dense_layer_t *layers;
} dense_network_t;

#define FLOAT_DIGIT 64

int getLayerCount(char *act_fname) {
    FILE *f;
    int layer_count = 0;

    ssize_t read;
    char *line = NULL;
    size_t len = 0;

    if ((f = fopen(act_fname, "r")) == NULL) {
        fprintf(stderr, "Error- Unable to open %s\n", act_fname);
        return -1;
    }

    while ((read = getline(&line, &len, f)) != -1) {
        layer_count++;
    }

    fclose(f);
    if (line) {
        free(line);
    }
    
    return layer_count;
}

int getLayerUnits(char *weight_fname, int *layers) {
    FILE *f;

    if ((f = fopen(weight_fname, "r")) == NULL) {
        fprintf(stderr, "Error- Unable to open %s\n", weight_fname);
        return -1;
    }

    char c;
    bool row_start = false;
    bool col_start = false;
    bool parse_ok = false;
    int row_size = 0;
    int elem_size = 0;
    int layer_idx = 0;
    int layer_count = 0;
    while ((c = fgetc(f)) != EOF) {
        // printf("%c", c);

        if (c == '[') {
            if (!row_start) {
                row_start = true;
            } else { 
                col_start = true;
            }
        } else if (c == ']') {
            if (col_start) {
                col_start = false;

                if (parse_ok) {
                    row_size++;
                    parse_ok = false;
                }              
            } else {
                row_start = false;
            }
        } else if (c == ',') {
            if (parse_ok) {
                elem_size++;
            }
        } else if (c == '\n') {
            row_start = false;
            col_start = false;
            parse_ok = false;
            if (layer_idx == 0) {
                layers[layer_count] = row_size;
                layer_count++;
                layers[layer_count] = elem_size/row_size+1;
                layer_count++;
            } else {
                if ((layer_idx % 2) == 0) {
                    layers[layer_count] = elem_size/row_size+1;
                    layer_count++;
                }
            }
            layer_idx++;
            elem_size = 0;
            row_size = 0;
        } else {
            parse_ok = true;
        }
    }

}

void getActivation(char *act_fname, activation *funcs) {
    FILE *f;
    int layer_count = 0;

    char *line = NULL;
    size_t len = 0;
    ssize_t nread;

    if ((f = fopen(act_fname, "r")) == NULL) {
        fprintf(stderr, "Error- Unable to open %s\n", act_fname);
        return;
    }

    char act_name[16] = {0};
    while ((nread = getline(&line, &len, f)) != -1) {
        memset(act_name, 0, 16);

        /* Remove newline and EOS */
        strncpy(act_name, line, strlen(line) - 2);

        if (strcmp(act_name, "relu") == 0) {
            funcs[layer_count] = ACTIVATION_RELU;
        } else if (strcmp(act_name, "sigmoid") == 0) {
            funcs[layer_count] = ACTIVATION_SIGMOID;
        } else if (strcmp(act_name, "tanh") == 0) {
            funcs[layer_count] = ACTIVATION_TANH;
        } else if (strcmp(act_name, "linear") == 0) {
            funcs[layer_count] = ACTIVATION_LINEAR;
        } else if (strcmp(act_name, "leaky") == 0) {
            funcs[layer_count] = ACTIVATION_LEAKYRELU;
        } 

        layer_count++;
    }

    free(line);
    fclose(f);
}


void parseStringToWeights(char *line, float ***w) {
    char c;
    bool row_start = false;
    bool col_start = false;
    bool parse_ok = false;
    char str_float[FLOAT_DIGIT];
    int str_float_idx = 0;
    float real_float;
    int row_size = 0;
    int elem_size = 0;

    while ((c = *line) != '\0') {
        if (c == '[') {
            if (!row_start) {
                row_start = true;
            } else {
                col_start = true;
            }
        } else if (c == ']') {
            if (col_start) {
                col_start = false;

                if (parse_ok) {
                    real_float = atof(str_float);
                    (*w)[elem_size][row_size] = real_float;
                    row_size++;
                    elem_size = 0;
                    memset(str_float, 0, FLOAT_DIGIT);
                    str_float_idx = 0;
                    parse_ok = false;
                }              
            } else { 
                row_start = false;
            }
        } else if (c == ',') {
            if (parse_ok) {
                real_float = atof(str_float);
                (*w)[elem_size][row_size] = real_float;
                elem_size++;
                memset(str_float, 0, FLOAT_DIGIT);
                str_float_idx = 0;
            }
        } else {
            str_float[str_float_idx] = c;
            str_float_idx++;
            parse_ok = true;
        }

        line++;
    }
}

void parseStringToBiases(char *line, float **b) {
    char c;
    bool row_start = false;
    bool col_start = false;
    bool parse_ok = false;
    char str_float[FLOAT_DIGIT];
    int str_float_idx = 0;
    float real_float;
    int row_size = 0;
    int elem_size = 0;

    while ((c = *line) != '\0') {
        if (c == '[') {
            if (!row_start) {
                row_start = true;
            } else {
                col_start = true;
            }
        } else if (c == ']') {
            if (col_start) {
                col_start = false;

                if (parse_ok) {
                    real_float = atof(str_float);
                    (*b)[elem_size] = real_float;
                    row_size++;
                    elem_size = 0;
                    memset(str_float, 0, FLOAT_DIGIT);
                    str_float_idx = 0;
                    parse_ok = false;
                }              
            } else { 
                row_start = false;
            }
        } else if (c == ',') {
            if (parse_ok) {
                real_float = atof(str_float);
                (*b)[elem_size] = real_float;
                elem_size++;
                memset(str_float, 0, FLOAT_DIGIT);
                str_float_idx = 0;
            }
        } else {
            str_float[str_float_idx] = c;
            str_float_idx++;
            parse_ok = true;
        }

        line++;
    }
}

void updateLayerWeightsFromFile(char *weight_fname, dense_layer_t *layer, uint32_t layer_idx) {
    FILE *f;

    ssize_t read;
    char *line = NULL;
    size_t len = 0;

    if ((f = fopen(weight_fname, "r")) == NULL) {
        fprintf(stderr, "Error- Unable to open %s\n", weight_fname);
        return;
    }

    int file_row_count = 0;
    while ((read = getline(&line, &len, f)) != -1) {
        if (file_row_count / 2 == layer_idx) {
            if (file_row_count % 2 == 0) {
                printf("w[%ld]: %s", strlen(line), line);
                parseStringToWeights(line, &layer->w);
            } else {
                printf("b[%ld]: %s", strlen(line), line);
                parseStringToBiases(line, &layer->b);
            }
        }
        file_row_count++;
    }


    fclose(f);
    free(line);
}

dense_network_t *createNetwork(char *weight_fname, char *act_fname) {
    /* Get layer count */
    /* Get list of activation function */
    /* Get list of layer units *?
    /* Modify layer unit's weight based on file */
    /* Iterate all layer and predict */
}

dense_input_t *getNetworkPredict(dense_network_t network, dense_input_t x) {

}

int main(int argc, char *argv[]) {
    char filename[64] = "tests/weights_xor.txt";
    FILE *f;

    if ((f = fopen(filename, "r")) == NULL) {
        fprintf(stderr, "Error- Unable to open %s\n", filename);
        exit(EXIT_FAILURE);
    }

    char c;
    bool row_start = false;
    bool col_start = false;
    bool parse_ok = false;
    char str_float[FLOAT_DIGIT];
    int str_float_idx = 0;
    float real_float;
    int row_size = 0;
    int elem_size = 0;
    while ((c = fgetc(f)) != EOF) {
        // printf("%c", c);

        if (c == '[') {
            if (!row_start) { // COL has not started
                row_start = true;
                // printf("\n\t>\n");
            } else { // Start COL when [ is found if ROW already start
                col_start = true;
                // printf("\n\t\t>\n");
            }
        } else if (c == ']') {
            if (col_start) { // Stop processing COL-wise
                col_start = false;
                // printf("\n\t\t<\n");

                if (parse_ok) {
                    real_float = atof(str_float);
                    printf("%.6f ", real_float);
                    row_size++;
                    memset(str_float, 0, FLOAT_DIGIT);
                    str_float_idx = 0;
                    parse_ok = false;
                }              

                printf("\n");
            } else { // Stop processing ROW
                row_start = false;
                // printf("  <\n");
            }
        } else if (c == ',') {
            if (parse_ok) {
                real_float = atof(str_float);
                printf("%.6f ", real_float);
                elem_size++;
                memset(str_float, 0, FLOAT_DIGIT);
                str_float_idx = 0;
            }
        } else if (c == '\n') {
            row_start = false;
            col_start = false;
            memset(str_float, 0, FLOAT_DIGIT);
            str_float_idx = 0;
            parse_ok = false;
            printf("shape [%d, %d]\n", row_size, elem_size/row_size+1);
            elem_size = 0;
            row_size = 0;
            printf("\n");
        } else {
            str_float[str_float_idx] = c;
            str_float_idx++;
            parse_ok = true;
        }
    }

    char act_fname[64] = "tests/acts_xor.txt";
    int layer_count = getLayerCount(act_fname);
    printf("layer_count: %d\n", layer_count);

    activation *funcs = (activation *)malloc(layer_count * sizeof(activation));
    getActivation(act_fname, funcs);

    for (int i = 0; i < layer_count; i++) {
        printf("layer-%d activation: %d\n", i+1, funcs[i]);
    }

    char weight_fname[64] = "tests/weights_xor.txt";
    int *layers = (int *)malloc((layer_count + 1) * sizeof(int));
    getLayerUnits(weight_fname, layers);

    for (int i = 0; i < layer_count + 1; i++) {
        printf("Layer-%d units: %d\n", i, layers[i]);
    }
    
    
    for (int layer_idx = 0; layer_idx < layer_count; layer_idx++) {
        printf("layer-idx [%d]\n", layer_idx);
        dense_layer_t *test_layer = denseLayerInit(layers[layer_idx], layers[layer_idx+1], INIT_ONE, ACTIVATION_RELU);

        /* Modify weight */
        updateLayerWeightsFromFile("tests/weights_xor.txt", test_layer, layer_idx);

        denseLayerShow(*test_layer);
        denseLayerDeinit(test_layer);
    }

    
    free(funcs);
    free(layers);



    return 0;
}