#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "vector.h"
#include "ray.h"

typedef struct _Camera {
    double ar;  // aspect ratio
    double vw_h;// viewport height
    double vw_w;// viewport width
    double fl;  // focal length

    V3 orig;
    V3 hori;
    V3 vert;
    V3 llc; // lower left corner
} Camera;

typedef Camera* CameraPtr;

Ray Camera_get_ray(CameraPtr, double u, double v);
#endif
