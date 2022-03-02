#include <stdarg.h>

#include "dasvaca.h"
#include "shapes.h"

#include "sphere.h"

struct _ShapeObject {
    void *shape;
    int shape_type;
};

struct _ShapeObjectArray {
    int count;
    ShapeObjectPtr * at;
};


/**** Methods Arrays ***
 * Must preserved order of enum 
 *******************************/

typedef bool  (*fnHit)(ShapeObjectPtr, HitRecordPtr, RayPtr, double, double);
typedef void* (*fnInit)(va_list attr);
typedef void  (*fnDestroy)(void *);

const fnHit hit_methods[] = {
    sphereHit,
};

const fnInit init_methods[] = {
    sphereInit,
};

const fnDestroy destroy_methods[] = {
    sphereDestroy,
};

/**********
 * Shapes Methods Implementation
 *********/

bool 
shapeHit(ShapeObjectPtr o, HitRecordPtr h, RayPtr r, double t_min, double t_max) {
    return hit_methods[o->shape_type](o, h, r, t_min, t_max);
}

ShapeObjectPtr 
shapeObjectInit(int type, ...) {
    dv_true_or_panik((type < MAX_SHAPE && type >= 0),
            "invalid shape type, got '%i'",,type);

    ShapeObjectPtr o = dv_malloc(sizeof(*o));
    o->shape_type = (ShapeType) type;

    va_list attr;
    va_start(attr, type);

    o->shape = init_methods[type](attr);
    
    va_end(attr);

    return o;
}

void *
shapeGet(ShapeObjectPtr o) {
    return o->shape;
}

void 
shapeObjectDestroy(ShapeObjectPtr o) {
    destroy_methods[o->shape_type](o->shape);

    free(o);
}

ShapeObjectArrayPtr 
shapeArrayInit(int size, ShapeObjectPtr a, ...) {
    dv_true_or_panik((size > 0), "Expected positive size, got %i",, size);

    ShapeObjectArrayPtr array = dv_malloc(sizeof(*array));
    
    array->at = dv_malloc(size * sizeof(*array->at));
    array->count = size;

    va_list objects;
    va_start(objects, a);
    
    array->at[0] = a;
    for(int i = 1; i < size; i++) {
        array->at[i] = va_arg(objects, ShapeObjectPtr);
    }

    va_end(objects);

    return array;
}

void 
shapeArrayDestroy(ShapeObjectArrayPtr array) {
    for (int i = 0; i < array->count; i++) {
        shapeObjectDestroy(array->at[i]);
    }
    free(array->at);
    free(array);
}

bool
shapeClosestHit(ShapeObjectArrayPtr objects, RayPtr r, HitRecordPtr h, double t_min, double t_max) {
   bool has_hitted = false;
   double closest_hit = t_max;

   HitRecord curr_hit;

   for (int i = 0; i < objects->count; i++) {
        ShapeObjectPtr shape = objects->at[i];

        if (shapeHit(shape, &curr_hit, r, t_min, closest_hit)) {
            has_hitted = true;
            closest_hit = curr_hit.t; 
            *h = curr_hit;
        }
   }

   return has_hitted;
}
