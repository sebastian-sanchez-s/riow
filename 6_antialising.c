#include "lib/ppm.h"
#include "lib/vector.h"
#include "lib/ray.h"
#include "lib/shapes.h"
#include "lib/camera.h"
#include "lib/random.h"

#include <stdio.h>
#include <stdbool.h>
#include <math.h>

typedef union PPM_Color Color; 

#define MAX_COLOR 255

V3 ray_color(RayPtr r, ShapeObjectArray targets) {
    HitRecord h;

    if (shapeClosestHit(targets, r, &h, 0, 500)) {
        V3 color = {
            .x = .5*(h.normal.x+1.0),
            .y = .5*(h.normal.y+1.0),
            .z = .5*(h.normal.z+1.0)
        };
        return color;
    }

    V3 unit_dir = V3_unit(&r->dir);
    double t = 0.5 * (unit_dir.y + 1.0);

    V3 color = {
        .x = (1.0 - 0.5*t),
        .y = (1.0 - 0.3*t),
        .z = 1 
    };

    return color;
}

void write_color(int row, int col, V3 pixel_color, int samples_per_pixel) {
    double scale = 1.0/samples_per_pixel;

    pixel_color = V3_scale(&pixel_color, scale);

    Color color = {{
        .r = pixel_color.x * MAX_COLOR,
        .g = pixel_color.y * MAX_COLOR,
        .b = pixel_color.z * MAX_COLOR
    }};

    PPM_set(row, col, color);
}

int main() {
    /* Image */
    double aspect_ratio = 16.0/9.0;
    int w = 400;
    int h = w/aspect_ratio;
    int samples_per_pixel = 100;

    PPM_init(h, w);
    
    /* Camera */
    Camera cam = {
        .ar     = aspect_ratio,
        .vw_h   = 2.0,
        .vw_w   = round(cam.vw_h * cam.ar),
        .fl     = 1.0,
        .orig   = {0, 0, 0},
        .hori   = V3_create(cam.vw_w, 0, 0),
        .vert   = V3_create(0, cam.vw_h, 0),
        .llc    = V3_create(
            cam.orig.x - cam.hori.x/2 - cam.vert.x/2,
            cam.orig.y - cam.hori.y/2 - cam.vert.y/2,
            cam.orig.z - cam.hori.z/2 - cam.vert.z/2 - cam.fl 
        )
    };
    
    
    /* Drawing/render */
    // Objects
    ShapeObjectArray targets = shapeArrayInit(2,
            shapeObjectInit(SPHERE, V3_create(0, 0, -1), 0.5),
            shapeObjectInit(SPHERE, V3_create(0, -100.5, -1), 100.0)
    );

    for(int row = h-1; row >= 0; --row) {
        for(int col = 0; col < w; col++) {
            V3 pixel_color = {0};
            
            // Antialising
            for (int s = 0; s < samples_per_pixel; ++s) {
                double u = (double)((double)col + uniform()) / (w-1);
                double v = (double)((double)row + uniform()) / (h-1);
                
                Ray r = Camera_get_ray(&cam, u, v);

                V3 new_color = ray_color(&r, targets);
                pixel_color = V3_nsum(2, &pixel_color, &new_color);
            }
            
            write_color(row, col, pixel_color, samples_per_pixel);
        }
    }

    PPM_save_as("output/6_antialiasing.ppm");

    PPM_destroy();
    shapeArrayDestroy(targets);
}
