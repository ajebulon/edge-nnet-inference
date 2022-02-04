#include <stdio.h>
#include <stdlib.h>

#include "layer.h"

/* Create dense input object */
dense_input_t *denseInputInit(uint32_t x_count, float *x) {
    dense_input_t *new = (dense_input_t *)malloc(sizeof(dense_input_t));
    new->x_count = x_count;
    new->x = x;
    return new;
}

/* Delete dense input object */
void denseInputDeinit(dense_input_t *this) {
    free(this->x);
    free(this);
}

/* Dense input object show */
void denseInputShow(dense_input_t this) {
    printf("x.shape = (%d, 1)\n", this.x_count);
    for (int i = 0; i < this.x_count; i++) {
        printf(" > x[%d] = %.6f\n", i, this.x[i]);
    }
}

/* Create dense layer object */
dense_layer_t *denseLayerInit(uint32_t prev_num_unit, uint32_t this_num_unit, initalization method, activation func) {
    dense_layer_t *new = (dense_layer_t *)malloc(sizeof(dense_layer_t));
    new->prev_num_unit = prev_num_unit;
    new->this_num_unit = this_num_unit;
    new->func = func;

    /* Initialize w-matrix */
    new->w = (float **)malloc(new->this_num_unit * sizeof(float *));
    for (int row = 0; row < new->this_num_unit; row++) {
        new->w[row] = (float *)malloc(new->prev_num_unit * sizeof(float));
        for (int col = 0; col < new->prev_num_unit; col++) {
            new->w[row][col] = initValue(method);
        }
    }

    /* Initialize b-matrix */
    new->b = (float *)malloc(new->this_num_unit * sizeof(float));
    for (int row = 0; row < new->this_num_unit; row++) {
        new->b[row] = initValue(method);
    }

    return new;
}

/* Delete dense layer object */
void denseLayerDeinit(dense_layer_t *this) {
    for (int row = 0; row < this->this_num_unit; row++) {
        free(this->w[row]);
    }
    free(this->w);
    free(this->b);
    free(this);
}

/* Dense layer object show */
void denseLayerShow(dense_layer_t this) {
    printf("w.shape = (%d, %d) | activation: %d\n", this.this_num_unit, this.prev_num_unit, this.func);
    for (int row = 0; row < this.this_num_unit; row++) {
        for (int col = 0; col < this.prev_num_unit; col++) {
            printf(" > w[%d][%d] = %.6f\n", row, col, this.w[row][col]);
        }
    }
    printf("b.shape = (%d, 1)\n", this.this_num_unit);
    for (int row = 0; row < this.this_num_unit; row++) {
        printf(" > b[%d] = %.6f\n", row, this.b[row]);
    }
}

/* Single dense layer forward */
dense_input_t *denseForwardStep(dense_input_t input, dense_layer_t layer) {
    dense_input_t *a = (dense_input_t *)malloc(sizeof(dense_input_t));
    activation func = layer.func;
    a->x_count = layer.this_num_unit;
    
    /* Matrix multiplication */
    a->x = (float *)malloc(a->x_count * sizeof(float));
    for (int row = 0; row < a->x_count; row++) {
        a->x[row] = 0;
        for (int col = 0; col < layer.prev_num_unit; col++) {
            a->x[row] += layer.w[row][col] * input.x[col];
        }
    }

    /* Add bias */
    for (int row = 0; row < a->x_count; row++) {
        a->x[row] += layer.b[row];
    }

    /* Activation function */
    for (int row = 0; row < a->x_count; row++) {
        a->x[row] = actValue(a->x[row], func);
    }

    return a;
}