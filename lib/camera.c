#include "vector.h"
#include "ray.h"
#include "camera.h"
#include <stdlib.h>

Ray cameraGetRay(CameraPtr c, double u, double v) {
    Vec3 no = vec3Scale(&c->orig, -1);
    Vec3 sh = vec3Scale(&c->hori, u);
    Vec3 sv = vec3Scale(&c->vert, v);

    Vec3 ray_dir = vec3NSum(4, &c->llc, &sh, &sv, &no);

    Ray r = {.orig = c->orig, .dir = ray_dir};
    return r;
}
