#include "lib/ppm.h"
#include "lib/vector.h"
#include "lib/ray.h"
#include "lib/shapes.h"
#include "lib/camera.h"
#include "lib/random.h"

#include <stdio.h>
#include <stdbool.h>
#include <math.h>

#define MAX_COLOR 255

Vec3 ray_color(RayPtr r, ShapeObjectArray targets) {
    HitRecord h;

    if (shapeClosestHit(targets, r, &h, 0, 500)) {
        Vec3 color = {
            .x = .5*(h.normal.x+1.0),
            .y = .5*(h.normal.y+1.0),
            .z = .5*(h.normal.z+1.0)
        };
        return color;
    }

    Vec3 unit_dir = vec3Unit(&r->dir);
    double t = 0.5 * (unit_dir.y + 1.0);

    Vec3 color = {
        .x = (1.0 - 0.5*t),
        .y = (1.0 - 0.3*t),
        .z = 1 
    };

    return color;
}

void write_color(int row, int col, Vec3 pixel_color, int samples_per_pixel) {
    double scale = 1.0/samples_per_pixel;

    pixel_color = vec3Scale(&pixel_color, scale);

    PPMColor color = {{
        .r = pixel_color.x * MAX_COLOR,
        .g = pixel_color.y * MAX_COLOR,
        .b = pixel_color.z * MAX_COLOR
    }};

    ppmSet(row, col, color);
}

int main() {
    /* Image */
    double aspect_ratio = 16.0/9.0;
    int w = 400;
    int h = w/aspect_ratio;
    int samples_per_pixel = 100;

    ppmInit(h, w);
    
    /* Camera */
    Camera cam = {
        .ar     = aspect_ratio,
        .vw_h   = 2.0,
        .vw_w   = round(cam.vw_h * cam.ar),
        .fl     = 1.0,
        .orig   = {0, 0, 0},
        .hori   = vec3Create(cam.vw_w, 0, 0),
        .vert   = vec3Create(0, cam.vw_h, 0),
        .llc    = vec3Create(
            cam.orig.x - cam.hori.x/2 - cam.vert.x/2,
            cam.orig.y - cam.hori.y/2 - cam.vert.y/2,
            cam.orig.z - cam.hori.z/2 - cam.vert.z/2 - cam.fl 
        )
    };
    
    
    /* Drawing/render */
    // Objects
    ShapeObjectArray targets = shapeArrayInit(2,
            shapeObjectInit(SPHERE, vec3Create(0, 0, -1), 0.5),
            shapeObjectInit(SPHERE, vec3Create(0, -100.5, -1), 100.0)
    );

    for(int row = h-1; row >= 0; --row) {
        for(int col = 0; col < w; col++) {
            Vec3 pixel_color = {0};
            
            // Antialising
            for (int s = 0; s < samples_per_pixel; ++s) {
                double u = (double)((double)col + randUniform()) / (w-1);
                double v = (double)((double)row + randUniform()) / (h-1);
                
                Ray r = cameraGetRay(&cam, u, v);

                Vec3 new_color = ray_color(&r, targets);
                pixel_color = vec3NSum(2, &pixel_color, &new_color);
            }
            
            write_color(row, col, pixel_color, samples_per_pixel);
        }
    }

    ppmSaveAs("output/6_antialiasing.ppm");

    ppmDestroy();
    shapeArrayDestroy(targets);
}
