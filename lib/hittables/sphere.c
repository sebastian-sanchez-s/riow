#include <stdbool.h>
#include <stdlib.h>
#include <math.h>

#include "hittable.h"
#include "vector.h"
#include "ray.h"
#include "sphere.h"


bool Sphere_hit(Sphere_ptr s, Ray_ptr r, HitRecord_ptr h, double t_min, double t_max) {
    /* Determine if ray hits sphere */
    V3 neg_center = V3_scale(&s->center, -1);
    V3 oc = V3_nsum(2, &r->orig, &neg_center);

    double a  = V3_dot(&r->dir, &r->dir);
    double hb = V3_dot(&oc, &r->dir);
    double c  = V3_dot(&oc, &oc) - s->rad*s->rad;

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

    h->t      = root;
    h->point  = Ray_at(r, root);

    V3 out_normal = V3_nsum(2, &h->point, &neg_center);
    out_normal = V3_scale(&out_normal, 1.0/s->rad);
    
    set_face_normal(h, r, &out_normal);

    return true;
}
