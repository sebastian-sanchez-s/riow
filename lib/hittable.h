#ifndef _HITTABLE_H_
#define _HITTABLE_H_

#include <stdbool.h>

#include "vector.h"
#include "ray.h"

typedef struct {
    double t;
    V3 point;
    V3 normal;
    bool front_face;
} HitRecord;

typedef HitRecord* HitRecord_ptr;
void set_face_normal(HitRecord_ptr, Ray_ptr, V3_ptr);

#endif
