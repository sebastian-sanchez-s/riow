#ifndef VECTOR3_H
#define VECTOR3_H

typedef struct Vector3 {
    double x, y, z;
} Vec3;

typedef Vec3* Vec3Ptr;

Vec3 vec3Create(double x, double y, double z);
Vec3 vec3Scale(Vec3Ptr, double);
Vec3 vec3Product(Vec3Ptr, Vec3Ptr);
Vec3 vec3Sum(Vec3Ptr, ...);
Vec3 vec3NSum(int, Vec3Ptr, ...);
Vec3 vec3Cross(Vec3Ptr, Vec3Ptr);
Vec3 vec3Unit(Vec3Ptr);
Vec3 vec3LowerBound(Vec3Ptr, double);
Vec3 vec3RandomInUnitSphere();

double vec3Norm(Vec3Ptr);
double vec3Dot(Vec3Ptr, Vec3Ptr);

#endif
