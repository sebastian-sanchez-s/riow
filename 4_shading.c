#include <stdio.h>
#include <stdbool.h>
#include <math.h>

#include "lib/ppm.h"
#include "lib/shapes.h"
#include "lib/sphere.h"
#include "lib/vector.h"
#include "lib/ray.h"

#define MAX_COLOR 255

PPMColor ray_color(ShapeObjectPtr o, RayPtr r) {
    if (shapeHit(o, r, 0, 500)) {
        /* -1 <= unit        <= 1
         *  0 <= unit+1      <= 2
         *  0 <= .5*(unit+1) <= 1 */
        PPMColor color = {{
            .r = .5 * (o->hit_record->normal.x + 1.0) * MAX_COLOR,
            .g = .5 * (o->hit_record->normal.y + 1.0) * MAX_COLOR,
            .b = .5 * (o->hit_record->normal.z + 1.0) * MAX_COLOR
        }};
        return color;
    }

    Vec3 unit_dir = vec3Unit(&r->dir);
    double t = 0.5 * (unit_dir.y + 1.0);

    PPMColor color = {{
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

    ppmInit(h, w);
    
    double vw_h = 2.0;
    double vw_w = round(vw_h * aspect_ratio);
    double focal_length = 1.0;
    
    /* Camera */
    Vec3 origin     = {0.0};
    Vec3 horizontal = {.x = vw_w, .y =  0.0, .z = 0.0};
    Vec3 vertical   = {.x =  0.0, .y = vw_h, .z = 0.0};
    Vec3 llc = { // lower left corner
        .x = origin.x - horizontal.x/2 - vertical.x/2,
        .y = origin.y - horizontal.y/2 - vertical.y/2,
        .z = origin.z - horizontal.z/2 - vertical.z/2 - focal_length
    };
    
    /* Drawing/render */
    Ray ray = {.orig = origin};
    ShapeObjectPtr o = shapeObjectInit(SPHERE, vec3Create(0, 0, -1), 0.5);

    for(int row = 0; row < h; row++) {
        for(int col = 0; col < w; col++) {
            double u = (double)col / (w-1);
            double v = (double)row / (h-1);

            Vec3 scale_h = vec3Scale(&horizontal, u);
            Vec3 scale_v = vec3Scale(&vertical, v);

            ray.dir = vec3NSum(3, &llc, &scale_h, &scale_v);
            
            PPMColor color = ray_color(o, &ray);
            ppmSet(row, col, color);
        }
    }

    ppmSaveAs("output/4_shading.ppm");
    ppmDestroy();

    shapeObjectDestroy(o);
}
