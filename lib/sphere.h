#ifndef _SPHERE_H_
#define _SPHERE_H_

#include <stdbool.h>

#include "hittable.h"
#include "vector.h"
#include "ray.h"

typedef struct {
    V3 center;
    double rad;
} Sphere;

typedef Sphere* Sphere_ptr;

bool Sphere_hit(Sphere_ptr, Ray_ptr, HitRecord_ptr, double t_min, double t_max);
bool Sphere_closest_hit(Sphere_ptr s[], Ray_ptr r, HitRecord_ptr h, double t_min, double t_max);

#endif
