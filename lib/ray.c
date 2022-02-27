#include "ray.h"
#include <stdlib.h>


Vec3 rayAt(RayPtr ray, double t) {
    // P(t) = orig + t*direction
    Vec3 aux = vec3Scale(&ray->dir, t);
    return vec3NSum(2, &ray->orig, &aux);
}
