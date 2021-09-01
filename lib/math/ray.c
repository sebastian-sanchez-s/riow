#include "ray.h"
#include <stdlib.h>


V3 Ray_at(Ray_ptr ray, double t) {
    // P(t) = orig + t*direction
    V3 aux = V3_scale(&ray->dir, t);
    return V3_sum(&ray->orig, &aux);
}
