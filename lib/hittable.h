#ifndef _HITTABLE_H_
#define _HITTABLE_H_

#include <stdbool.h>

#include "vector.h"
#include "ray.h"

typedef struct _HitRecord {
    double t;
    Vec3 point;
    Vec3 normal;
    bool front_face;
    int material_type;
} HitRecord;

typedef HitRecord* HitRecordPtr;

void hrSetFaceNormal(HitRecordPtr, RayPtr, Vec3Ptr);
#endif
