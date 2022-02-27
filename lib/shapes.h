#ifndef _SHAPE_H_
#define _SHAPE_H_

#include <stdarg.h>

#include "shape_object.h"

#include "ray.h"
#include "sphere.h"

typedef enum _ShapeType {
    SPHERE=0,
    MAX_SHAPE
} ShapeType;

struct _ShapeObjectArray {
    int count;
    ShapeObjectPtr * at;
};

typedef struct _ShapeObjectArray* ShapeObjectArray;

/******************
 * Methods Arrays
 * ****************/
typedef bool (*fnHit)(ShapeObjectPtr, RayPtr, double, double);
const fnHit hit_methods[] = {
    sphereHit,
};

typedef void* (*fnInit)(va_list attr);
const fnInit init_methods[] = {
    sphereInit,
};

typedef void (*fnDestroy)(void *attr);
const fnDestroy destroy_methods[] = {
    sphereDestroy,
};

/************
 * Methods wrappers
 *******************/
ShapeObjectPtr shapeObjectInit(ShapeType, ...);

void shapeObjectDestroy(ShapeObjectPtr);

bool shapeHit(ShapeObjectPtr, RayPtr, double, double);
bool shapeClosestHit(ShapeObjectArray, RayPtr, HitRecordPtr, double t_min, double t_max);

ShapeObjectArray shapeArrayInit(int size, ShapeObjectPtr, ...);
void shapeArrayDestroy(ShapeObjectArray);

#endif
