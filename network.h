#ifndef NETWORK_H
#define NETWORK_H

#include <stdint.h>

#include "layer.h"

#define FLOAT_DIGIT 64

typedef struct dense_network {
    uint32_t layer_count;
    dense_layer_t **layers;
} dense_network_t;

/* Get number of layer from file */
int getLayerCountFromFile(char *act_fname);

/* Retrieve number of units per layer, including input layer, from file */
int getLayerUnitsWithInputFromFile(char *weight_fname, int *layers);

/* Parse line string to retrieve weights in 2D shape */
void parseStringToWeights(char *line, float ***w);

/* Parse line string to retrieve biases in 2D shape */
void parseStringToBiases(char *line, float **b);

/* Update initialized layer with parsed line from file */
void updateLayerWeightsFromFile(char *weight_fname, dense_layer_t *layer, uint32_t layer_idx);

/* Update initialized layer with parsed activation function from file */
void updateLayerActivationFromFile(char *act_fname, dense_layer_t *layer, uint32_t layer_idx);

/* Create network from file */
dense_network_t *createNetworkFromFile(char *weight_fname, char *act_fname);

/* Show created network */
void denseNetworkShow(dense_network_t dense_net);

/* Deinitialized created network */
void denseNetworkDeinit(dense_network_t *dense_net);

/* Network inference */
dense_input_t *getNetworkPredict(dense_network_t network, dense_input_t x);

#endif /* NETWORK_H */