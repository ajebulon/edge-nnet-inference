#ifndef INITIALIZATION_H
#define INITIALIZATION_H

typedef enum {
    INIT_ZERO,
    INIT_ONE,
    INIT_RANDOM
} initalization;

/* Return zero value */
float initZero();

/* Return one value */
float initOne();

/* Return random value from -0.5 to 0.5 */
float initRandom();

/* Return value based on specified method */
float initValue(initalization method);

#endif /* INITIALIZATION_H */