#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "activation.h"
#include "layer.h"

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

    while ((nread = getline(&line, &len, f)) != -1) {
        printf("line [%ld]: %s", strlen(line), line);

        printf("ret: %d\n", strcmp(line, "relu"));
        if (strcmp(line, "relu") == 13) {
            funcs[layer_count] = ACTIVATION_RELU;
        } else if (strcmp(line, "sigmoid") == 13) {
            funcs[layer_count] = ACTIVATION_SIGMOID;
        } else if (strcmp(line, "tanh") == 13) {
            funcs[layer_count] = ACTIVATION_TANH;
        } else if (strcmp(line, "linear") == 13) {
            funcs[layer_count] = ACTIVATION_LINEAR;
        } else if (strcmp(line, "leaky") == 13) {
            funcs[layer_count] = ACTIVATION_LEAKYRELU;
        } 

        layer_count++;
    }

    free(line);
    fclose(f);
}


dense_input_t *getNetworkPredict(char *weight_fname, char *act_fname, dense_input_t x) {
    /* Get layer count */
    /* Get list of activation function */
    /* Get list of layer units *?
    /* Modify layer unit's weight based on file */
    /* Iterate all layer and predict */
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
    
    
    for (int layer = 1; layer < layer_count; layer++) {
        dense_layer_t *test_layer = denseLayerInit(layers[layer-1], layers[layer], INIT_ONE);
        denseLayerShow(*test_layer);
        denseLayerDeinit(test_layer);
    }

    
    free(funcs);
    free(layers);




    // int c;
    // bool group_start = false;
    // bool array_start = false;
    // char str_float[64];
    // int str_float_idx = 0;
    // float real_float;
    // int array_cnt = 0;

    // while ((c = fgetc(f)) != EOF) {
    //     printf("%c", (char)c);

    //     if (c == '[') {
    //         if (!group_start) {
    //             group_start = true;
    //             printf("  >\n");
    //             continue;
    //         } else {
    //             array_start = true;
    //             printf("    >>\n");
    //             continue;
    //         }
    //     } else if (c == ',' || c == ']') {
    //         real_float = atof(str_float);
    //         printf("\nval: %.6f\n\n", real_float);
    //         memset(str_float, 0, 64);
    //         str_float_idx = 0;
    //     } else if (c == ']') {
    //         if (array_start) {                
    //             array_start = false;
    //             printf("    <<\n");
    //             continue;
    //         } else {
    //             group_start = false;
    //             printf("  <\n");
    //             continue;
    //         }
    //     } else if (c == '\n') {
    //         array_start = false;
    //         group_start = false;
    //         memset(str_float, 0, 64);
    //         str_float_idx = 0;
    //         continue;
    //     } else {
    //         str_float[str_float_idx] = c;
    //         str_float_idx++;
    //     }
    // }

    return 0;
}