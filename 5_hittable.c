#include <stdio.h>
#include <stdbool.h>
#include <math.h>

#include "lib/ppm.h"
#include "lib/shapes.h"
#include "lib/vector.h"
#include "lib/ray.h"

#define MAX_COLOR 255

typedef union PPM_Color Color; 

Color ray_color(RayPtr r, ShapeObjectArray targets) {
    HitRecord h;

    if (shapeClosestHit(targets, r, &h, 0, 500)) {
        Color color = {{
            .r = .5*(h.normal.x+1.0)*MAX_COLOR,
            .g = .5*(h.normal.y+1.0)*MAX_COLOR,
            .b = .5*(h.normal.z+1.0)*MAX_COLOR
        }};
        return color;
    }

    V3 unit_dir = V3_unit(&r->dir);
    double t = 0.5 * (unit_dir.y + 1.0);

    Color color = {{
        .r = (1.0 - 0.5*t) * MAX_COLOR,
        .g = (1.0 - 0.3*t) * MAX_COLOR,
        .b = MAX_COLOR
    }};

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
    V3 origin     = {0.0};
    V3 horizontal = {.x = vw_w, .y =  0.0, .z = 0.0};
    V3 vertical   = {.x =  0.0, .y = vw_h, .z = 0.0};
    V3 llc = { // lower left corner
        .x = origin.x - horizontal.x/2 - vertical.x/2,
        .y = origin.y - horizontal.y/2 - vertical.y/2,
        .z = origin.z - horizontal.z/2 - vertical.z/2 - focal_length
    };
    
    /* Drawing/render */
    // Objects
    Ray ray = {.orig = origin};

    ShapeObjectArray targets = shapeArrayInit(2,
            shapeObjectInit(SPHERE, V3_create(0, 0, -1), 0.5),
            shapeObjectInit(SPHERE, V3_create(0, -100.5, -1), 100.0)
    );

    for(int row = 0; row < h; row++) {
        for(int col = 0; col < w; col++) {
            double u = (double)col / (w-1);
            double v = (double)row / (h-1);

            V3 scale_h = V3_scale(&horizontal, u);
            V3 scale_v = V3_scale(&vertical, v);

            ray.dir = V3_nsum(3, &llc, &scale_h, &scale_v);
            
            Color color = ray_color(&ray, targets);
            PPM_set(row, col, color);
        }
    }

    PPM_save_as("output/5_hittable.ppm");
    PPM_destroy();

    shapeArrayDestroy(targets);
}
