#ifndef VECTOR3_H
#define VECTOR3_H

typedef struct Vector3 {
    double x, y, z;
} V3;

typedef V3* V3Ptr;

V3 V3_create(double x, double y, double z);
V3 V3_scale(V3Ptr, double);
V3 V3_sum(V3Ptr, ...);
V3 V3_nsum(int, V3Ptr, ...);
V3 V3_cross(V3Ptr, V3Ptr);
V3 V3_unit(V3Ptr);
V3 V3_lower_bound(V3Ptr, double);
V3 V3_random_in_unit_sphere();

double V3_norm(V3Ptr);
double V3_dot(V3Ptr, V3Ptr);

#endif
