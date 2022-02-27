#include "vector.h"
#include "ray.h"
#include "camera.h"
#include <stdlib.h>

Ray Camera_get_ray(CameraPtr c, double u, double v) {
    V3 no = V3_scale(&c->orig, -1);
    V3 sh = V3_scale(&c->hori, u);
    V3 sv = V3_scale(&c->vert, v);

    V3 ray_dir = V3_nsum(4, &c->llc, &sh, &sv, &no);

    Ray r = {.orig = c->orig, .dir = ray_dir};
    return r;
}
