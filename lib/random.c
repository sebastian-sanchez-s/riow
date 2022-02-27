#include <stdlib.h>
#include "random.h"

double randUniform() {
    return (float)rand() / (RAND_MAX + 1.0);
}

double randBetween(double min, double max) {
    return randUniform()*(max-min) + min;
}
