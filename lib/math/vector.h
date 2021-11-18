#ifndef VECTOR3_H
#define VECTOR3_H

typedef struct Vector3 {
    double x, y, z;
} V3;

typedef V3* V3_ptr;

V3 V3_create(double x, double y, double z);
V3 V3_scale(V3_ptr, double);
V3 V3_sum(V3_ptr, ...);
V3 V3_nsum(int, V3_ptr, ...);
V3 V3_cross(V3_ptr, V3_ptr);
V3 V3_unit(V3_ptr);
V3 V3_lower_bound(V3_ptr, double);

double V3_norm(V3_ptr);
double V3_dot(V3_ptr, V3_ptr);

#endif
