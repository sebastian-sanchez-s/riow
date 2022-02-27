#include "ray.h"
#include <stdlib.h>


V3 Ray_at(RayPtr ray, double t) {
    // P(t) = orig + t*direction
    V3 aux = V3_scale(&ray->dir, t);
    return V3_nsum(2, &ray->orig, &aux);
}
