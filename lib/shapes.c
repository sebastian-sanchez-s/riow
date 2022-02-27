#include <stdarg.h>
#include "dasvaca.h"
#include "shapes.h"
#include "hittable.h"

bool 
shapeHit(ShapeObjectPtr o, RayPtr r, double t_min, double t_max) {
    return hit_methods[o->shape_type](o, r, t_min, t_max);
}

ShapeObjectPtr 
shapeObjectInit(ShapeType type, ...) {
    dv_true_or_panik((type < MAX_SHAPE && type >= 0),
            "invalid shape type, got '%i'",,type);

    ShapeObjectPtr o = dv_malloc(sizeof(*o));
    o->shape_type = (ShapeType) type;

    o->hit_record = dv_malloc(sizeof(*o->hit_record));

    va_list attr;
    va_start(attr, type);

    o->shape = init_methods[type](attr);
    
    va_end(attr);

    return o;
}

void 
shapeObjectDestroy(ShapeObjectPtr o) {
    destroy_methods[o->shape_type](o->shape);

    free(o->hit_record);
    free(o);
}

ShapeObjectArray 
shapeArrayInit(int size, ShapeObjectPtr a, ...) {
    dv_true_or_panik((size > 0), "Expected positive size, got %i",, size);

    ShapeObjectArray array = dv_malloc(sizeof(*array));
    
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
shapeArrayDestroy(ShapeObjectArray array) {
    for (int i = 0; i < array->count; i++) {
        shapeObjectDestroy(array->at[i]);
    }
    free(array->at);
    free(array);
}

bool
shapeClosestHit(ShapeObjectArray objects, RayPtr r, HitRecordPtr h, double t_min, double t_max) {
   bool has_hitted = false;
   double closest_hit = t_max;

   for (int i = 0; i < objects->count; i++) {
        ShapeObjectPtr shape = objects->at[i];

        if (shapeHit(shape, r, t_min, closest_hit)) {
            has_hitted = true;
            closest_hit = shape->hit_record->t; 
            *h = *shape->hit_record;
        }
   }

   return has_hitted;
}
