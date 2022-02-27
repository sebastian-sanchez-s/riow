#ifndef RAY_H
#define RAY_H

#include "vector.h"

typedef struct _Ray {
    Vec3 orig;
    Vec3 dir;
} Ray;

typedef Ray* RayPtr;

Vec3 rayAt(RayPtr, double);

#endif
