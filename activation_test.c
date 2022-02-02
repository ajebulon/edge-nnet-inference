#include <stdio.h>
#include <assert.h>

#include "activation.h"

int main(int argc, char *argv[])
{
    float z, a;

    /* ReLU test */
    z = -0.3;
    a = actRelu(z);
    printf("ReLU(%.2f) = %.2f\n", z, a);

    z = 0.3;
    a = actRelu(z);
    printf("ReLU(%.2f) = %.2f\n", z, a);


    /* Sigmoid test */
    z = -10;
    a = actSigmoid(z);
    printf("Sigmoid(%.2f) = %.2f\n", z, a);

    z = 0;
    a = actSigmoid(z);
    printf("Sigmoid(%.2f) = %.2f\n", z, a);

    z = 10;
    a = actSigmoid(z);
    printf("Sigmoid(%.2f) = %.2f\n", z, a);


    /* Linear test */
    z = -0.3;
    a = actLinear(z);
    printf("Linear(%.2f) = %.2f\n", z, a);

    z = 0.3;
    a = actLinear(z);
    printf("Linear(%.2f) = %.2f\n", z, a);

    /* TanH test */
    z = -10;
    a = actTanh(z);
    printf("TanH(%.2f) = %.2f\n", z, a);

    z = 0;
    a = actTanh(z);
    printf("TanH(%.2f) = %.2f\n", z, a);

    z = 10;
    a = actTanh(z);
    printf("TanH(%.2f) = %.2f\n", z, a);

    /* Leaky ReLU */
    z = -3;
    a = actLeakyRelu(z);
    printf("Leaky ReLU(%.2f) = %.2f\n", z, a);

    z = 0.3;
    a = actLeakyRelu(z);
    printf("Leaky ReLU(%.2f) = %.2f\n", z, a);


    return 0;
}