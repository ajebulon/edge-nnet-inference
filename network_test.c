#include <stdio.h>
#include <stdlib.h>

#include "network.h"


int main(int argc, char *argv[]) {

    /* Given input filename of activation function and weights */
    char act_fname[64] = "tests/acts_mix.txt";
    char weight_fname[64] = "tests/weights_mix.txt";

    // Create network
    dense_network_t *dense_net = NULL;
    dense_net = createNetworkFromFile(weight_fname, act_fname);
    printf("Network\n==============================\n");
    printf("Total trainable params: %d\n", getDenseNetworkNumOfTrainableParams(*dense_net));
    denseNetworkShow(*dense_net);
    printf("\n");

    // Create sample input
    dense_input_t *test_input = NULL;
    float *x_test = (float *)malloc(3 * sizeof(float));
    x_test[0] = 5.0;
    x_test[1] = 1.0;
    x_test[2] = 0.0;
    test_input = denseInputInit(3, x_test);
    printf("Input\n==============================\n");
    denseInputShow(*test_input);
    printf("\n");

    dense_input_t *y_hat = NULL;
    y_hat = getNetworkPredict(*dense_net, *test_input);
    printf("Output\n==============================\n");
    denseInputShow(*y_hat);
    printf("\n");

    // Cleanup
    denseInputDeinit(y_hat);
    denseNetworkDeinit(dense_net);
    denseInputDeinit(test_input);

    return 0;
}