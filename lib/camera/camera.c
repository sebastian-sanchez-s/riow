#include "vector.h"
#include "ray.h"
#include "camera.h"
#include <stdlib.h>

Ray Camera_get_ray(Camera_ptr c, double u, double v) {
    V3 no = V3_scale(&c->orig, -1);
    V3 sh = V3_scale(&c->hori, u);
    V3 sv = V3_scale(&c->vert, v);

    V3 ray_dir = V3_sum(&c->llc, &sh, &sv, &no, NULL);

    Ray r = {.orig = c->orig, .dir = ray_dir};
    return r;
}
