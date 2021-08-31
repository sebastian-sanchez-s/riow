#ifndef VECTOR3_H
#define VECTOR3_H

struct Vector3 {
    double x, y, z;
};

typedef struct Vector3* V3_ptr;

V3_ptr V3_build();
V3_ptr V3(V3_ptr result, double x, double y, double z);
V3_ptr V3_scale(V3_ptr result, V3_ptr v, double t);
V3_ptr V3_sum(V3_ptr result, V3_ptr v, V3_ptr w);
V3_ptr V3_cross(V3_ptr result, V3_ptr v, V3_ptr w);
V3_ptr V3_unit(V3_ptr result, V3_ptr v);

double V3_norm(V3_ptr v);
double V3_dot(V3_ptr v, V3_ptr w);

#endif
