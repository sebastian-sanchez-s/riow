#include <stdarg.h>
#include <stdbool.h>
#include <math.h>

#include "dasvaca.h"
#include "vector.h"
#include "ray.h"
#include "sphere.h"
#include "hittable.h"

struct _Sphere {
    Vec3 center;
    double rad;
};

void * 
sphereInit(va_list attr) {
    /* attr: Vec3 center, double rad */
    SpherePtr s = dv_malloc(sizeof(*s));
    
    s->center = va_arg(attr, Vec3);
    s->rad = va_arg(attr, double);

    return s;
}

void 
sphereDestroy(void *sphere) {
    free(sphere);
}

bool
sphereHit(ShapeObjectPtr o, HitRecordPtr h, RayPtr r, double t_min, double t_max) {
    SpherePtr sphere = (SpherePtr) shapeGet(o);
    /* Determine if ray hits sphere */
    Vec3 neg_center = vec3Scale(&sphere->center, -1);
    Vec3 oc = vec3NSum(2, &r->orig, &neg_center);

    double a  = vec3Dot(&r->dir, &r->dir);
    double hb = vec3Dot(&oc, &r->dir);
    double c  = vec3Dot(&oc, &oc) - sphere->rad * sphere->rad;

    double discriminant = hb*hb - a*c;

    if (discriminant < 0) {
        return false;
    }

    /* if hitted, determine if solutions are in the
     * acceptable range */
    double sqrtd = sqrt(discriminant);
    double root = (-hb-sqrtd)/a;

    if (root < t_min || t_max < root) {
        // let's see the other root
        root = (-hb+sqrtd)/a;
        if (root < t_min || t_max < root) {
            return false;
        }
    }

    h->t = root;
    h->point = rayAt(r, root);

    Vec3 out_normal = vec3NSum(2, &h->point, &neg_center);
    out_normal = vec3Scale(&out_normal, 1.0/sphere->rad);
    
    hrSetFaceNormal(h, r, &out_normal);

    return true;
}

