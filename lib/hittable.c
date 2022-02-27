#include "dasvaca.h"
#include "vector.h"
#include "ray.h"
#include "hittable.h"

void hrSetFaceNormal(HitRecordPtr h, RayPtr r, Vec3Ptr out_normal) {
    h->front_face = vec3Dot(&r->dir, out_normal) < 0;
    h->normal = vec3Scale(out_normal, h->front_face ? 1:-1);
}

HitRecordPtr hrInit() {
    HitRecordPtr h = dv_malloc(sizeof(*h));
    return h;
};

