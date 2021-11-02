#include <stdlib.h>
#include "random.h"

double uniform() {
    return (float)rand() / (RAND_MAX + 1.0);
}

double rand_between(double min, double max) {
    return uniform()*(max-min) + min;
}
