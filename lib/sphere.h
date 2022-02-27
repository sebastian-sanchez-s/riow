#ifndef _SPHERE_H_
#define _SPHERE_H_

#include <stdarg.h>
#include <stdbool.h>

#include "shape_object.h"
#include "vector.h"
#include "ray.h"

typedef struct _Sphere {
    V3 center;
    double rad;
} Sphere;

typedef Sphere* SpherePtr;

void * sphereInit(va_list attr);
void sphereDestroy(void *);

bool sphereHit(ShapeObjectPtr, RayPtr, double, double);

#endif
