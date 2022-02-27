#ifndef RAY_H
#define RAY_H

#include "vector.h"

typedef struct _Ray {
    V3 orig;
    V3 dir;
} Ray;

typedef Ray* RayPtr;

V3 Ray_at(RayPtr, double);

#endif
