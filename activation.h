#ifndef ACTIVATION_H
#define ACTIVATION_H

typedef enum {
    ACTIVATION_RELU,
    ACTIVATION_SIGMOID,
    ACTIVATION_LINEAR,
    ACTIVATION_TANH, 
    ACTIVATION_LEAKYRELU
} activation;

/* ReLU activation function */
float actRelu(float z); 

/* Sigmoid activation function */
float actSigmoid(float z); 

/* Linear activation function */
float actLinear(float z);

/* TanH activation function */
float actTanh(float z);

/* Leaky ReLU activation function */
float actLeakyRelu(float z); 

/* Return value based on specified activation function */
float actValue(float z, activation func);

#endif /* ACTIVATION_H */