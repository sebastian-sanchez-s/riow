#include <stdio.h>
#include <stdbool.h>
#include <math.h>

#include "lib/ppm.h"
#include "lib/shapes.h"
#include "lib/vector.h"
#include "lib/ray.h"

#define MAX_COLOR 255

typedef union PPM_Color Color; 

Color ray_color(ShapeObjectPtr o, RayPtr r) {
    if (shapeHit(o, r, 0, 500)) {
        Color color = {
            .r = MAX_COLOR,
            .g = 0,
            .b = 0
        };
        return color;
    }
    V3 unit = V3_unit(&r->dir);
    double t = 0.5 * (unit.y + 1.0);

    Color color = {
        .r = (float)(1.0 - 0.5*t) * MAX_COLOR,
        .g = (float)(1.0 - 0.3*t) * MAX_COLOR,
        .b = MAX_COLOR
    };
    return color;
}

int main() {
    /* Image */
    double aspect_ratio = 16.0/9.0;
    int w = 400;
    int h = w/aspect_ratio;

    PPM_init(h, w);
    
    double vw_h = 2.0;
    double vw_w = round(vw_h * aspect_ratio);
    double focal_length = 1.0;
    
    /* Camera */
    V3 direction  = {0.0};
    V3 origin     = {0.0};
    V3 horizontal = {.x = vw_w, .y =  0.0, .z = 0.0};
    V3 vertical   = {.x =  0.0, .y = vw_h, .z = 0.0};
    V3 llc = { // lower left corner
        .x = origin.x - horizontal.x/2 - vertical.x/2,
        .y = origin.y - horizontal.y/2 - vertical.y/2,
        .z = origin.z - horizontal.z/2 - vertical.z/2 - focal_length
    };
    
    /* Drawing/render */
    Ray ray = {.orig = origin, .dir = direction};

    ShapeObjectPtr sphere = shapeObjectInit(SPHERE, V3_create(0, 0, -1), 0.5);

    for(int row = 0; row < h; row++) {
        for(int col = 0; col < w; col++) {
            double u = (double)col / (w-1);
            double v = (double)row / (h-1);

            V3 scale_h = V3_scale(&horizontal, u);
            V3 scale_v = V3_scale(&vertical, v);

            ray.dir = V3_nsum(3, &llc, &scale_h, &scale_v);
            
            Color color = ray_color(sphere, &ray);
            PPM_set(row, col, color);
        }
    }

    PPM_save_as("output/3_sphere.ppm");
    PPM_destroy();

    shapeObjectDestroy(sphere);
}
