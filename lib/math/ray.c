#include "ray.h"
#include <stdlib.h>

Ray_ptr Ray_build() {
    Ray_ptr ray = calloc(1, sizeof(*ray));
    return ray;
}

Ray_ptr Ray(Ray_ptr ray, V3_ptr origin, V3_ptr direction) {
    if (ray == NULL) {
        ray = Ray_build();
    }
    ray->origin = origin;
    ray->direction = direction;
    return ray;
}

V3_ptr Ray_at(V3_ptr result, Ray_ptr ray, double t) {
    // P(t) = orig + t*direction
    return V3_sum(result, ray->origin, V3_scale(result, ray->direction, t));
}
