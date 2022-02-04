#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h> // gettimeofday

#include "network.h"

/* Get delta time in ms */
static double get_time_delta_in_ms(struct timeval ts, struct timeval te)
{
    return ((te.tv_sec - ts.tv_sec) * 1000) + ((te.tv_usec - ts.tv_usec) / 1000);
}

int main(int argc, char *argv[]) {

    /* Given input filename of activation function and weights */
    char act_fname[64] = "tests/acts_mix.txt";
    char weight_fname[64] = "tests/weights_mix.txt";

    // Create network
    dense_network_t *dense_net = NULL;
    dense_net = createNetworkFromFile(weight_fname, act_fname);
    printf("Network\n==============================\n");
    printf("Total trainable params: %d\n", getDenseNetworkNumOfTrainableParams(*dense_net));

    uint32_t epochs = 1e4;
    struct timeval start, now;
    gettimeofday(&start, NULL);
    for (int epoch = 0; epoch < epochs; epoch++) {

        if ((epoch % (epochs/10)) == 0) {
            gettimeofday(&now, NULL);
            printf("Epoch-%d: %.3fs\n",  epoch, get_time_delta_in_ms(start, now)/1e3);
        }
        
        // Create sample input
        dense_input_t *test_input = NULL;
        float *x_test = (float *)malloc(3 * sizeof(float));
        x_test[0] = 5.0;
        x_test[1] = 1.0;
        x_test[2] = 0.0;
        test_input = denseInputInit(3, x_test);

        // Get prediction
        dense_input_t *y_hat = NULL;
        y_hat = getNetworkPredict(*dense_net, *test_input);

        // Cleanup
        denseInputDeinit(y_hat);
        denseInputDeinit(test_input);
    }

    gettimeofday(&now, NULL);
    printf("Finished %d Epochs in %.3fs\n", epochs, get_time_delta_in_ms(start, now)/1e3);
    printf("  > Each inference takes %.3fus\n", get_time_delta_in_ms(start, now)*1e3/epochs);

    // Cleanup
    denseNetworkDeinit(dense_net);

    return 0;
}