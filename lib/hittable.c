#include "dasvaca.h"
#include "vector.h"
#include "ray.h"
#include "hittable.h"

void HT_set_face_normal(HitRecordPtr h, RayPtr r, V3Ptr out_normal) {
    h->front_face = V3_dot(&r->dir, out_normal) < 0;
    h->normal = V3_scale(out_normal, h->front_face ? 1:-1);
}

HitRecordPtr HitRecordInit() {
    HitRecordPtr h = dv_malloc(sizeof(*h));
    return h;
};

