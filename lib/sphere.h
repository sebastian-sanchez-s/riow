#ifndef _SPHERE_H_
#define _SPHERE_H_

#include <stdarg.h>
#include <stdbool.h>

#include "shapes.h"
#include "ray.h"

typedef struct _Sphere Sphere; 
typedef Sphere* SpherePtr;

void * sphereInit(va_list attr);
void sphereDestroy(void *);

bool sphereHit(ShapeObjectPtr, HitRecordPtr, RayPtr, double, double);
#endif
