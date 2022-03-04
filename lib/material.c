#include <stdlib.h>

#include "material.h"
#include "dasvaca.h"

/******** Objects ***************/
struct _Material {
    Vec3 albedo;
    MaterialType type;
};

MaterialPtr
materialInit(MaterialType t, Vec3 albedo) {
    MaterialPtr m = dv_malloc(sizeof(*m));
    
    m->albedo = albedo;
    m->type = t;

    return m;
}

void 
materialDestroy(MaterialPtr m) {
    free(m);
}

/******** Methods **************/
bool
lambertianScatter(MaterialPtr m, RayPtr in, RayPtr out, HitRecordPtr h, Vec3Ptr attenuation) {
    Vec3 random_in_unit_sphere = vec3RandomInUnitSphere();
    Vec3 out_dir = vec3NSum(2, &h->normal, &random_in_unit_sphere);

    *out = (Ray) {.orig = h->point, .dir = out_dir};

    *attenuation = m->albedo;
    return true;
}

bool metalScatter(MaterialPtr m, RayPtr in, RayPtr out, HitRecordPtr h, Vec3Ptr attenuation) {
    Vec3 insident = vec3Unit(&in->dir);
    
    // Calculate reflected ray: v - lambda*n, where lambda := 2*n.v
    float lambda = -2.0 * vec3Dot(&insident, &h->normal);
    Vec3 n = vec3Scale(&h->normal, lambda);
    *out = (Ray) { .orig = h->point, .dir = vec3NSum(2, &insident, &n)};

    *attenuation = m->albedo;

    return true;
}

typedef bool (*fnScatter)(MaterialPtr m, RayPtr in, RayPtr out, HitRecordPtr h, Vec3Ptr attenuation);
const fnScatter scatter_methods[] = {
    lambertianScatter,
    metalScatter
};

bool
materialScatter(MaterialPtr m, RayPtr in, RayPtr out, HitRecordPtr h, Vec3Ptr attenuation) {
   return scatter_methods[m->type](m, in, out, h, attenuation); 
}

