#ifndef _SHAPE_H_
#define _SHAPE_H_

#include <stdarg.h>

#include "hittable.h"
#include "ray.h"

/*** Supported shapes so far ***************************
 * TODO: Trying to move this so that creating new shapes
 * doesn't require modifying this file
 * *****************************************************/ 
typedef enum _ShapeType {
    SPHERE=0,
    MAX_SHAPE
} ShapeType;

/*******
 * Opaque objects
 ***********/
typedef struct _ShapeObject ShapeObject;
typedef ShapeObject* ShapeObjectPtr;

typedef struct _ShapeObjectArray ShapeObjectArray;
typedef ShapeObjectArray* ShapeObjectArrayPtr;
/************
 * Methods wrappers
 *******************/
ShapeObjectPtr shapeObjectInit(int shape_type, ...);

void shapeObjectDestroy(ShapeObjectPtr);

void *shapeGet(ShapeObjectPtr);

bool shapeHit(ShapeObjectPtr, HitRecordPtr, RayPtr, double, double);
bool shapeClosestHit(ShapeObjectArrayPtr, RayPtr, HitRecordPtr, double t_min, double t_max);

ShapeObjectArrayPtr shapeArrayInit(int size, ShapeObjectPtr, ...);
void shapeArrayDestroy(ShapeObjectArrayPtr);

#endif
