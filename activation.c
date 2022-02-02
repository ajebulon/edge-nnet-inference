#include <math.h>

#include "activation.h"

/* ReLU activation function */
float actRelu(float z) {
    if (z < 0) {
        return 0;
    } 

    return z;
}

/* Sigmoid activation function */
float actSigmoid(float z) {
    return 1 / (1 + expf(-z));
}

/* Linear activation function */
float actLinear(float z) {
    return z;
}

/* TanH activation function */
float actTanh(float z) {
    return ((expf(z) - expf(-z)) / (expf(z) + expf(-z)));
}

/* Leaky ReLU activation function */
float actLeakyRelu(float z) {
    if (z < 0) {
        return 0.01 * z;
    }

    return z;
}

/* Return value based on specified activation function */
float actValue(float z, activation func) {
    if (func == ACTIVATION_RELU) {
        return actRelu(z);
    } else if (func == ACTIVATION_SIGMOID) {
        return actSigmoid(z);
    } else if (func == ACTIVATION_LINEAR) {
        return actLinear(z);
    } else if (func == ACTIVATION_TANH) {
        return actTanh(z);
    } else if (func == ACTIVATION_LEAKYRELU) {
        return actLeakyRelu(z);
    }
}