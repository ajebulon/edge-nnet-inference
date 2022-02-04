#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "network.h"


/* Get number of layer from file */
int getLayerCountFromFile(char *act_fname) {
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


/* Retrieve number of units per layer, including input layer, from file */
int getLayerUnitsWithInputFromFile(char *weight_fname, int *layers) {
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

    fclose(f);
}


/* Parse line string to retrieve weights in 2D shape */
void parseStringToWeights(char *line, float ***w) {
    char c;
    bool row_start = false;
    bool col_start = false;
    bool parse_ok = false;
    char str_float[FLOAT_DIGIT] = {};
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


/* Parse line string to retrieve biases in 2D shape */
void parseStringToBiases(char *line, float **b) {
    char c;
    bool row_start = false;
    bool col_start = false;
    bool parse_ok = false;
    char str_float[FLOAT_DIGIT] = {};
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


/* Update initialized layer with parsed weights from file */
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
                parseStringToWeights(line, &layer->w);
            } else {
                parseStringToBiases(line, &layer->b);
            }
        }
        file_row_count++;
    }


    fclose(f);
    free(line);
}


/* Update initialized layer with parsed activation function from file */
void updateLayerActivationFromFile(char *act_fname, dense_layer_t *layer, uint32_t layer_idx) {
    FILE *f;
    int layer_count = 0;

    ssize_t read;
    char *line = NULL;
    size_t len = 0;

    if ((f = fopen(act_fname, "r")) == NULL) {
        fprintf(stderr, "Error- Unable to open %s\n", act_fname);
        return;
    }

    char act_name[16] = {0};
    int file_row_count = 0;
    while ((read = getline(&line, &len, f)) != -1) {
        if (file_row_count == layer_idx) {
            memset(act_name, 0, 16);

            /* Remove newline and EOS */
            strncpy(act_name, line, strlen(line) - 2);

            if (strcmp(act_name, "relu") == 0) {
                layer->func = ACTIVATION_RELU;
            } else if (strcmp(act_name, "sigmoid") == 0) {
                layer->func = ACTIVATION_SIGMOID;
            } else if (strcmp(act_name, "tanh") == 0) {
                layer->func = ACTIVATION_TANH;
            } else if (strcmp(act_name, "linear") == 0) {
                layer->func = ACTIVATION_LINEAR;
            } else if (strcmp(act_name, "leaky") == 0) {
                layer->func = ACTIVATION_LEAKYRELU;
            } 
        }
        
        file_row_count++;
    }

    free(line);
    fclose(f);
}

/* Create network from file */
dense_network_t *createNetworkFromFile(char *weight_fname, char *act_fname) {
    
    // Get layer count
    int layer_count = getLayerCountFromFile(act_fname);

    // Get network configuration
    int *layers = (int *)malloc((layer_count + 1) * sizeof(int));
    getLayerUnitsWithInputFromFile(weight_fname, layers);
    
    // Build network
    dense_network_t *dense_net = (dense_network_t *)malloc(sizeof(dense_network_t));
    dense_net->layer_count = layer_count;
    dense_net->layers = (dense_layer_t **)malloc((dense_net->layer_count) * sizeof(dense_layer_t *));

    for (int layer_idx = 0; layer_idx < dense_net->layer_count; layer_idx++) {
        dense_net->layers[layer_idx] = denseLayerInit(layers[layer_idx], layers[layer_idx+1], INIT_ONE, ACTIVATION_RELU);

        // Modify weight
        updateLayerWeightsFromFile(weight_fname, dense_net->layers[layer_idx], layer_idx);
        
        // Modify activation function
        updateLayerActivationFromFile(act_fname, dense_net->layers[layer_idx], layer_idx);
    }

    free(layers);

    return dense_net;
}


/* Show created network */
void denseNetworkShow(dense_network_t dense_net) {
    for (int layer_idx = 0; layer_idx < dense_net.layer_count; layer_idx++) {
        denseLayerShow(*dense_net.layers[layer_idx]);
    }
}

/* Get number of trainable parameters */
uint32_t getDenseNetworkNumOfTrainableParams(dense_network_t dense_net) {
    uint32_t num = 0;
    for (int layer_idx = 0; layer_idx < dense_net.layer_count; layer_idx++) {
        num += dense_net.layers[layer_idx]->this_num_unit * dense_net.layers[layer_idx]->prev_num_unit;
        num += dense_net.layers[layer_idx]->this_num_unit;
    }

    return num;
}

/* Deinitialized created network */
void denseNetworkDeinit(dense_network_t *dense_net) {
    for (int layer_idx = 0; layer_idx < dense_net->layer_count; layer_idx++) {
        denseLayerDeinit(dense_net->layers[layer_idx]);
    }
    free(dense_net->layers);
    free(dense_net);
}


/* Network inference */
dense_input_t *getNetworkPredict(dense_network_t network, dense_input_t x) {
    dense_layer_t *this_layer;
    dense_input_t *a = &x;

    for (int layer_idx = 0; layer_idx < network.layer_count; layer_idx++) {
        this_layer = network.layers[layer_idx];
        dense_input_t *a_temp = a;
        a = denseForwardStep(*a, *this_layer);

        if (layer_idx > 0) {
            denseInputDeinit(a_temp);
        }
    }
    return a;
}