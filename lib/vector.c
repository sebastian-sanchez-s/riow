#include "vector.h"
#include "random.h"
#include <stdlib.h>
#include <math.h>
#include <stdarg.h>

Vec3 vec3Create(double x, double y, double z) {
    return (Vec3) {.x = x, .y = y, .z = z };
}

Vec3 vec3Product(Vec3Ptr a, Vec3Ptr b) {
    return (Vec3) {a->x * b->x, a->y * b->y, a->z * b->z};
}

Vec3 vec3RandomInUnitSphere() {
    float theta = randBetween(0, 6.28);
    float phi = randBetween(0, 3.14);

    return vec3Create(sin(phi)*cos(theta), sin(phi)*sin(theta), cos(phi));
}

Vec3 vec3Scale(Vec3Ptr a, double t) {
    return (Vec3) {
        .x = a->x*t,
        .y = a->y*t,
        .z = a->z*t
    };
}

Vec3 vec3NSum(int n, Vec3Ptr a, ...) {
    if (n <= 1) {
        return *a;
    }

    Vec3 v = {0};
    va_list vector_list;
    va_start(vector_list, a);

    Vec3Ptr iter = a;
    while (n-- > 0) {
        v.x += iter->x;
        v.y += iter->y;
        v.z += iter->z;
        iter = va_arg(vector_list, Vec3Ptr);
    }

    va_end(vector_list);
    return v;
}

Vec3 vec3Sum(Vec3Ptr a, ...) {
    Vec3 v = {0};
    va_list ap;
    va_start(ap, a);

    Vec3Ptr iter;
    for (iter = a; iter != NULL; iter = va_arg(ap, Vec3Ptr)) {
        v.x += iter->x;
        v.y += iter->y;
        v.z += iter->z;
    }

    va_end(ap);
    return v;
}

Vec3 vec3Cross(Vec3Ptr a, Vec3Ptr b) {
    return (Vec3) {
        .x = a->y*b->z - a->z*b->y,
        .y = a->z*b->x - a->x*b->z,
        .z = a->x*b->y - a->y*b->x
    };
}

Vec3 vec3LowerBound(Vec3Ptr a, double e) {
    return (Vec3) {
        .x = a->x < e ? e: a->x,
        .y = a->y < e ? e: a->y,
        .z = a->z < e ? e: a->z
    };
}

Vec3 vec3Unit(Vec3Ptr a) {
    return vec3Scale(a, 1.0/vec3Norm(a));
}

double vec3Norm(Vec3Ptr a) {
    return sqrt(vec3Dot(a, a));
}

double vec3Dot(Vec3Ptr a, Vec3Ptr b) {
    return a->x*b->x + a->y*b->y + a->z*b->z;
}

