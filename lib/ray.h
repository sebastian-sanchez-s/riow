#ifndef RAY_H
#define RAY_H

#include "vector.h"

typedef struct _Ray {
    V3 orig;
    V3 dir;
} Ray;

typedef Ray* Ray_ptr;

V3 Ray_at(Ray_ptr, double);

#endif
