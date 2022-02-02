#include <time.h>
#include <stdlib.h>

#include "initialization.h"


/* Return zero value */
float initZero() {
    return 0;
}

/* Return one value */
float initOne() {
    return 1;
}

/* Return random value from -0.5 to 0.5 */
float initRandom() {
    return ((float)rand() / (float)RAND_MAX) - 0.5;
}

/* Return value based on specified method */
float initValue(initalization method) {
    if (method == INIT_ZERO) {
        return initZero();
    } else if (method == INIT_ONE) {
        return initOne();
    } else if (method == INIT_RANDOM) {
        return initRandom();
    }
}