#include "vector.h"
#include "random.h"
#include <stdlib.h>
#include <math.h>
#include <stdarg.h>

V3 V3_create(double x, double y, double z) {
    V3 v = {.x = x, .y = y, .z = z };
    return v;
}

V3 V3_random_in_unit_sphere() {
    float theta = rand_between(0, 6.28);
    float phi = rand_between(0, 3.14);

    return V3_create(sin(phi)*cos(theta), sin(phi)*sin(theta), cos(phi));
}

V3 V3_scale(V3_ptr a, double t) {
    V3 v = {
        .x = a->x*t,
        .y = a->y*t,
        .z = a->z*t
    };
    return v;
}

V3 V3_nsum(int n, V3_ptr a, ...) {
    if (n <= 1) {
        return *a;
    }

    V3 v = {0};
    va_list vector_list;
    va_start(vector_list, a);

    V3_ptr iter = a;
    while (n-- > 0) {
        v.x += iter->x;
        v.y += iter->y;
        v.z += iter->z;
        iter = va_arg(vector_list, V3_ptr);
    }

    va_end(vector_list);
    return v;
}

V3 V3_sum(V3_ptr a, ...) {
    V3 v = {0};
    va_list ap;
    va_start(ap, a);

    V3_ptr iter;
    for (iter = a; iter != NULL; iter = va_arg(ap, V3_ptr)) {
        v.x += iter->x;
        v.y += iter->y;
        v.z += iter->z;
    }

    va_end(ap);
    return v;
}

V3 V3_cross(V3_ptr a, V3_ptr b) {
    V3 v = {
        .x = a->y*b->z - a->z*b->y,
        .y = a->z*b->x - a->x*b->z,
        .z = a->x*b->y - a->y*b->x
    };
    return v;
}

V3 V3_lower_bound(V3_ptr a, double e) {
    V3 v = {
        .x = a->x < e ? e: a->x,
        .y = a->y < e ? e: a->y,
        .z = a->z < e ? e: a->z
    };
    return v;
}

V3 V3_unit(V3_ptr a) {
    return V3_scale(a, 1.0/V3_norm(a));
}

double V3_norm(V3_ptr a) {
    return sqrt(V3_dot(a, a));
}

double V3_dot(V3_ptr a, V3_ptr b) {
    return a->x*b->x + a->y*b->y + a->z*b->z;
}

