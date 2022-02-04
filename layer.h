#ifndef LAYER_H
#define LAYER_H

#include <stdint.h>

#include "activation.h"
#include "initialization.h"

typedef struct dense_layer {
    uint32_t prev_num_unit;
    uint32_t this_num_unit;
    float **w;
    float *b;
    activation func;
} dense_layer_t;

typedef struct dense_input {
    uint32_t x_count;
    float *x;
} dense_input_t;

/* Create dense input object */
dense_input_t *denseInputInit(uint32_t x_count, float *x);

/* Delete dense input object */
void denseInputDeinit(dense_input_t *this);

/* Dense input object show */
void denseInputShow(dense_input_t this);

/* Create dense layer object */
dense_layer_t *denseLayerInit(uint32_t prev_num_unit, uint32_t this_num_unit, initalization method);

/* Delete dense layer object */
void denseLayerDeinit(dense_layer_t *this);

/* Dense layer object show */
void denseLayerShow(dense_layer_t this);

/* Single dense layer forward */
dense_input_t *denseForwardStep(dense_input_t input, dense_layer_t layer, activation func);


#endif /* LAYER_H */