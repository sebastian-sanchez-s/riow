#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "vector.h"
#include "ray.h"

typedef struct _Camera {
    double ar;  // aspect ratio
    double vw_h;// viewport height
    double vw_w;// viewport width
    double fl;  // focal length

    Vec3 orig;
    Vec3 hori;
    Vec3 vert;
    Vec3 llc; // lower left corner
} Camera;

typedef Camera* CameraPtr;

Ray cameraGetRay(CameraPtr, double u, double v);
#endif
