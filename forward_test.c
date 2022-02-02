// #include <stdio.h>
// #include <stdlib.h>
// #include <stdint.h>
// #include <stdlib.h>
// #include <time.h> // time
// #include <string.h>

// #include "activation.h"



// input_t *feedForward(input_t input_value, layer_t layer_value, activation func) {
//     input_t *a = (input_t *)malloc(sizeof(input_t));
//     a->v_count = layer_value.this_layer_unit;
    
//     /* Matrix multiplication */
//     a->v = (float *)malloc(a->v_count * sizeof(float));
//     for (int i = 0; i < a->v_count; i++) {
//         a->v[i] = 0;
//         for (int col = 0; col < layer_value.prev_layer_unit; col++) {
//             a->v[i] += layer_value.w[i][col] * input_value.v[col];
//         }
//     }

//     /* Add bias */
//     for (int i = 0; i < a->v_count; i++) {
//         a->v[i] += layer_value.b[i];
//     }

//     /* Activation function */
//     for (int i = 0; i < a->v_count; i++) {
//         if (func == ACTIVATION_RELU) {
//             a->v[i] = relu(a->v[i]);
//         } else if (func == ACTIVATION_SIGMOID) {
//             a->v[i] = sigmoid(a->v[i]);
//         } else if (func == ACTIVATION_LINEAR) {
//             a->v[i] = linear(a->v[i]);
//         }
//     }

//     return a;
// }

// input_t *inputInit(uint32_t v_count, float *v) {
//     input_t *new_input = (input_t *)malloc(sizeof(input_t));
//     new_input->v_count = v_count;
//     new_input->v = v;
//     return new_input;
// }

// void inputDeinit(input_t *input_in) {
//     free(input_in->v);
//     free(input_in);
// }

// void inputShow(input_t input_in) {
//     printf("v-matrix [%dx1]:\n", input_in.v_count);
//     for (int i = 0; i < input_in.v_count; i++) {
//         printf("> v[%d] = %.2f\n", i, input_in.v[i]);
//     }
// }

// layer_t *layerInit(uint32_t prev_layer_unit, uint32_t this_layer_unit, initalization method) {
//     layer_t *new_layer = (layer_t *)malloc(sizeof(layer_t));

//     new_layer->prev_layer_unit = prev_layer_unit;
//     new_layer->this_layer_unit = this_layer_unit;

//     new_layer->w = (float **)malloc(new_layer->this_layer_unit * sizeof(float *));
//     for (int row = 0; row < new_layer->this_layer_unit; row++) {
//         new_layer->w[row] = (float *)malloc(new_layer->prev_layer_unit * sizeof(float));
//         for (int col = 0; col < new_layer->prev_layer_unit; col++) {
//             new_layer->w[row][col] = initValue(method);
//         }
//     }

//     new_layer->b = (float *)malloc(new_layer->this_layer_unit * sizeof(float));
//     for (int i = 0; i < new_layer->this_layer_unit; i++) {
//         new_layer->b[i] = initValue(method);
//     }

//     return new_layer;
// }

// void layerShow(layer_t layer_in) {
//     printf("w-matrix [%dx%d]\n", layer_in.this_layer_unit, layer_in.prev_layer_unit);
//     for (int row = 0; row < layer_in.this_layer_unit; row++) {
//         for (int col = 0; col < layer_in.prev_layer_unit; col++) {
//             printf("> w[%d][%d] = %.2f\n", row, col, layer_in.w[row][col]);
//         }
//     }

//     printf("b-matrix [%dx1]\n", layer_in.this_layer_unit);
//     for (int i = 0; i < layer_in.this_layer_unit; i++) {
//             printf("> b[%d] = %.2f\n", i, layer_in.b[i]);
//     }
// }

// void layerDeinit(layer_t *layer_in) {
//     for (int row = 0; row < layer_in->this_layer_unit; row++) {
//         free(layer_in->w[row]);
//     }
//     free(layer_in->w);
//     free(layer_in->b);
//     free(layer_in);
// }

// int main(int argc, char *argv[]) {

//     srand(time(NULL));

//     // input_t *this_input = NULL;
//     // float v[2] = {0.5, 0.1};
//     // this_input = inputInit(2, v);
//     // inputShow(*this_input);

//     // layer_t *layer_1;
//     // layer_1 = layerInit(2, 4, INIT_RANDOM);

//     // input_t *a;
//     // a = feedForward(*this_input, *layer_1, ACTIVATION_RELU);


//     // layer_t *layer_2;
//     // layer_2 = layerInit(4, 1, INIT_RANDOM);

//     // this_input = a;
//     // a = feedForward(*this_input, *layer_2, ACTIVATION_RELU);
//     // inputShow(*a);



//     input_t *this_input = NULL;
//     float v[2] = {0.5, 0.1};
//     this_input = inputInit(2, v);
//     inputShow(*this_input);

//     uint32_t layer_units[] = {8, 8, 1};
//     // activation layer_activations[] = {ACTIVATION_RELU, ACTIVATION_RELU, ACTIVATION_RELU, ACTIVATION_SIGMOID};
//     activation layer_activations[] = {ACTIVATION_RELU, ACTIVATION_RELU, ACTIVATION_RELU};
//     uint32_t layer_count = 3;

//     for (int i = 0; i < layer_count; i++) {
//         printf("Processing layer-%d\n", i);
//         layer_t *this_layer = layerInit(this_input->v_count, layer_units[i], INIT_ONE);

//         input_t *temp_input;
//         temp_input = feedForward(*this_input, *this_layer, layer_activations[i]);

//         layerDeinit(this_layer);
//         inputDeinit(this_input);

//         this_input = temp_input;
//     }

//     inputShow(*this_input);

//     // for (int i = 0; i < 0; i++) {
//     //     layer_t *this_layer;
//     //     input_t *a;

//     //     this_layer = layerInit(this_input->v_count, layer_units[i], INIT_RANDOM);
//     //     a = feedForward(*this_input, *this_layer, layer_activations[i]);

//     //     layerDeinit(this_layer);
//     //     inputDeinit(this_input);
//     // }

//     // inputShow(*a);

//     return 0;
// }


#include <stdio.h>
#include <stdlib.h>
#include <stdint.h> // uint32_t

#include "activation.h"
#include "initialization.h"

typedef struct dense_layer {
    uint32_t prev_num_unit;
    uint32_t this_num_unit;
    float **w;
    float *b;
} dense_layer_t;

typedef struct dense_input {
    uint32_t x_count;
    float *x;
} dense_input_t;


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
        printf(" > x[%d] = %.2f\n", i, this.x[i]);
    }
}

/* Create dense layer object */
dense_layer_t *denseLayerInit(uint32_t prev_num_unit, uint32_t this_num_unit, initalization method)
{
    dense_layer_t *new = (dense_layer_t *)malloc(sizeof(dense_layer_t));
    new->prev_num_unit = prev_num_unit;
    new->this_num_unit = this_num_unit;

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
    printf("w.shape = (%d, %d)\n", this.this_num_unit, this.prev_num_unit);
    for (int row = 0; row < this.this_num_unit; row++) {
        for (int col = 0; col < this.prev_num_unit; col++) {
            printf(" > w[%d][%d] = %.2f\n", row, col, this.w[row][col]);
        }
    }
    printf("b.shape = (%d, 1)\n", this.this_num_unit);
    for (int row = 0; row < this.this_num_unit; row++) {
        printf(" > b[%d] = %.2f\n", row, this.b[row]);
    }
}

/* Single dense layer forward */
dense_input_t *denseForwardStep(dense_input_t input, dense_layer_t layer, activation func) {
    dense_input_t *a = (dense_input_t *)malloc(sizeof(dense_input_t));
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


int main(int argc, char *argv[]) {
    
    /* Test dense input */
    dense_input_t *this_input = NULL;
    float *x = (float *)malloc(3 * sizeof(float));
    x[0] = 0.5;
    x[1] = 0.1;
    x[2] = -0.3;
    this_input = denseInputInit(3, x);
    denseInputShow(*this_input);

    /* Test dense layer */
    dense_layer_t *this_layer = NULL;
    this_layer = denseLayerInit(3, 1, INIT_ONE);
    denseLayerShow(*this_layer);

    /* Test dense forward step */
    dense_input_t *forward = NULL;
    forward = denseForwardStep(*this_input, *this_layer, ACTIVATION_RELU);
    denseInputShow(*forward);

    /* Cleanup */
    denseInputDeinit(this_input);
    denseLayerDeinit(this_layer);
    denseInputDeinit(forward);

    /* Network test */
    dense_input_t *test_input = NULL;
    float *x_test = (float *)malloc(4 * sizeof(float));
    x_test[0] = 0.5;
    x_test[1] = 0.1;
    x_test[2] = -0.1;
    x_test[3] = -0.5;
    test_input = denseInputInit(4, x_test);
    denseInputShow(*test_input);

    uint32_t layer_count = 4;
    uint32_t layers[4] = {4, 3, 2, 1};
    activation acts[4] = {ACTIVATION_RELU, ACTIVATION_RELU, ACTIVATION_RELU, ACTIVATION_SIGMOID};

    for (int layer = 0; layer < layer_count; layer++) {
        dense_layer_t *test_layer = denseLayerInit(test_input->x_count, layers[layer], INIT_RANDOM);

        dense_input_t *temp = test_input;
        test_input = denseForwardStep(*test_input, *test_layer, acts[layer]);

        denseLayerDeinit(test_layer);
        denseInputDeinit(temp);
    }

    denseInputShow(*test_input);
    denseInputDeinit(test_input);

    return 0;
}
