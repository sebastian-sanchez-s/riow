#ifndef _HITTABLE_H_
#define _HITTABLE_H_

#include <stdbool.h>

#include "vector.h"
#include "ray.h"

typedef struct _HitRecord {
    double t;
    V3 point;
    V3 normal;
    bool front_face;
} HitRecord;

typedef HitRecord* HitRecordPtr;

void HT_set_face_normal(HitRecordPtr, RayPtr, V3Ptr);
#endif
