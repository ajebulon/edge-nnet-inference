#include <stdio.h>
#include <stdlib.h>
#include <stdint.h> // uint32_t

#include "layer.h"

int main(int argc, char *argv[]) {
    
    printf("Unit Test\n");
    printf("==============================\n");
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
    this_layer = denseLayerInit(3, 1, INIT_ONE, ACTIVATION_RELU);
    denseLayerShow(*this_layer);

    /* Test dense forward step */
    dense_input_t *forward = NULL;
    forward = denseForwardStep(*this_input, *this_layer);
    denseInputShow(*forward);

    /* Cleanup */
    denseInputDeinit(this_input);
    denseLayerDeinit(this_layer);
    denseInputDeinit(forward);

    /* Network test */
    printf("\n");
    printf("Network Test\n");
    printf("==============================\n");
    dense_input_t *test_input = NULL;
    float *x_test = (float *)malloc(4 * sizeof(float));
    x_test[0] = 0.5;
    x_test[1] = 0.1;
    x_test[2] = -0.1;
    x_test[3] = -0.5;
    test_input = denseInputInit(4, x_test);
    denseInputShow(*test_input);

    uint32_t layer_count = 4;
    uint32_t layers[4] = {2, 3, 4, 1};
    activation acts[4] = {ACTIVATION_LINEAR, ACTIVATION_LINEAR, ACTIVATION_LINEAR, ACTIVATION_LINEAR};
    // activation acts[4] = {ACTIVATION_RELU, ACTIVATION_RELU, ACTIVATION_RELU, ACTIVATION_SIGMOID};

    for (int layer = 0; layer < layer_count; layer++) {
        dense_layer_t *test_layer = denseLayerInit(test_input->x_count, layers[layer], INIT_ONE, acts[layer]);
        denseLayerShow(*test_layer);

        dense_input_t *temp = test_input;
        test_input = denseForwardStep(*test_input, *test_layer);

        denseLayerDeinit(test_layer);
        denseInputDeinit(temp);
    }

    denseInputShow(*test_input);
    denseInputDeinit(test_input);

    return 0;
}
