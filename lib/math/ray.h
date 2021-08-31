#ifndef RAY_H
#define RAY_H

#include "vector.h"

struct Ray {
    V3_ptr origin;
    V3_ptr direction;
};

typedef struct Ray* Ray_ptr;

Ray_ptr Ray_build();
Ray_ptr Ray(Ray_ptr, V3_ptr origin, V3_ptr direction);
V3_ptr Ray_at(V3_ptr, Ray_ptr,  double t);

#endif
