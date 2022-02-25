#include "vector.h"
#include "ray.h"
#include "hittable.h"

void set_face_normal(HitRecord_ptr h, Ray_ptr r, V3_ptr out_normal) {
    h->front_face = V3_dot(&r->dir, out_normal) < 0;
    h->normal = V3_scale(out_normal, h->front_face ? 1:-1);
}
