#ifndef _MATERIAL_H_
#define _MATERIAL_H_

#include <stdbool.h>

#include "hittable.h"
#include "vector.h"
#include "ray.h"

typedef enum {LAMBERTIAN, METAL} MaterialType;

typedef struct _Material Material;
typedef Material* MaterialPtr;

MaterialPtr materialInit(MaterialType, Vec3 albedo);
void materialDestroy(MaterialPtr);

bool materialScatter(MaterialPtr, RayPtr in, RayPtr out, HitRecordPtr h, Vec3Ptr attenuation);

#endif
