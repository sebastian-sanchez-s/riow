#ifndef _SHAPE_OBJECT_H_
#define _SHAPE_OBJECT_H_

#include <stdbool.h>
#include <stdarg.h>

#include "hittable.h"
#include "ray.h"

typedef struct _ShapeObject ShapeObject;
typedef ShapeObject* ShapeObjectPtr;

struct _ShapeObject {
    void *shape;
    int shape_type;

    HitRecordPtr hit_record;
};

#endif
