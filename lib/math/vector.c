#include "vector.h"
#include <stdlib.h>
#include <math.h>

V3_ptr V3_build() {
    V3_ptr v = calloc(1, sizeof(*v));
    return v;
}

V3_ptr V3(V3_ptr result, double x, double y, double z) {
    if (result == NULL) {
        result = V3_build();
    }
    
    result->x = x;
    result->y = y;
    result->z = z;

    return result;
}

V3_ptr V3_scale(V3_ptr result, V3_ptr v, double t) {
    result->x = v->x*t;
    result->y = v->y*t;
    result->z = v->z*t;
    return result;
}

V3_ptr V3_sum(V3_ptr result, V3_ptr v, V3_ptr w) {
    result->x = v->x + w->x;
    result->y = v->y + w->y;
    result->z = v->z + w->z;
    return result;
}

V3_ptr V3_cross(V3_ptr result, V3_ptr v, V3_ptr w) {
    result->x = v->y*w->z - v->z*w->y;
    result->y = v->z*w->x - v->x*w->z;
    result->z = v->x*w->y - v->y*w->x;
    return result;
}

V3_ptr V3_unit(V3_ptr result, V3_ptr v) {
    return V3_scale(result, v, 1.0/V3_norm(v));
}

double V3_norm(V3_ptr v) {
    return sqrt(V3_dot(v, v));
}

double V3_dot(V3_ptr v, V3_ptr w) {
    return v->x*w->x + v->y+w->y + v->z*w->z;
}

