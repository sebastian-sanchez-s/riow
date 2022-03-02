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

#define TMAX 1000.0
#define TMIN 0.01

Vec3 ray_color(RayPtr r, ShapeObjectArrayPtr targets, int ncollision) {
    if (ncollision <= 0) {
        return vec3Create(0, 0, 0);
    }

    HitRecord h;
    if (shapeClosestHit(targets, r, &h, TMIN, TMAX)) {
        Vec3 unit = vec3RandomInUnitSphere();
        unit = vec3Scale(&unit, vec3Dot(&unit, &h.normal) > 0.0 ? 1.0: -1.0);

        Vec3 target = vec3NSum(2, &h.point, &unit);

        r->orig = h.point;
        r->dir  = vec3NSum(2, &target, &unit);
        
        Vec3 color = ray_color(r, targets, ncollision - 1);

        return vec3Scale(&color, 0.5);
    }

    Vec3 unit_dir = vec3Unit(&r->dir);
    double t = 0.5 * (unit_dir.y + 1.0);

    return vec3Create(1.0 - 0.5*t, 1.0 - 0.3*t, 1.0);
}

void write_color(int row, int col, Vec3 pixel_color, int samples_per_pixel) {
    double scale = 1.0/samples_per_pixel;

    pixel_color = vec3Scale(&pixel_color, scale);
    pixel_color.x = sqrt(pixel_color.x);
    pixel_color.y = sqrt(pixel_color.y);
    pixel_color.z = sqrt(pixel_color.z);

    PPMColor color = {{
        .r = pixel_color.x * MAX_COLOR,
        .g = pixel_color.y * MAX_COLOR,
        .b = pixel_color.z * MAX_COLOR
    }};

    ppmSet(row, col, color);
}

int main() {
    /* Image */
    const double aspect_ratio = 16.0/9.0;
    const int w = 400;
    const int h = w/aspect_ratio;
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
    ShapeObjectArrayPtr targets = shapeArrayInit(2,
            shapeObjectInit(SPHERE, vec3Create(0, 0, -1), 0.5),
            shapeObjectInit(SPHERE, vec3Create(0, -100.5, -1), 100.0)
    );
    
    /* Drawing constants */
    const int samples_per_pixel = 50;
    const int max_collisions = 25;

    for(int row = h-1; row >= 0; --row) {
        for(int col = 0; col < w; col++) {
            Vec3 pixel_color = {0};
            
            // Antialising
            for (int s = 0; s < samples_per_pixel; ++s) {
                double u = (double)((double)col + randUniform()) / (w-1);
                double v = (double)((double)row + randUniform()) / (h-1);
                
                Ray r = cameraGetRay(&cam, u, v);

                Vec3 new_color = ray_color(&r, targets, max_collisions);
                pixel_color = vec3NSum(2, &pixel_color, &new_color);
            }

            write_color(row, col, pixel_color, samples_per_pixel);
        }
    }

    ppmSaveAs("output/7_mate_reflection.ppm");

    ppmDestroy();
    shapeArrayDestroy(targets);
}
