#ifndef CAMERA_H
#define CAMERA_H

#include "vector.h"
#include "ray.h"

typedef struct _Camera {
    double ar;  // aspect ratio
    double vw_h;// viewport height
    double vh_w;// viewport width
    double fl;  // focal length

    V3 orig;
    V3 hori;
    V3 vert;
    V3 llc;
} Camera;

typedef Camera* Camera_ptr;

Ray Camera_get_ray(Camera_ptr, double u, double v);
#endif
