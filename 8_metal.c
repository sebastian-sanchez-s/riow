#include "lib/ppm.h"
#include "lib/vector.h"
#include "lib/ray.h"
#include "lib/shapes.h"
#include "lib/camera.h"
#include "lib/random.h"
#include "lib/material.h"

#include <stdio.h>
#include <stdbool.h>
#include <math.h>

#define MAX_COLOR 255

#define TMAX 1000.0
#define TMIN 0.01

Vec3 ray_color(RayPtr r, ShapeObjectArrayPtr targets, MaterialPtr material[], int ncollision) {
    if (ncollision <= 0) {
        return vec3Create(0, 0, 0);
    }

    HitRecord h;
    if (shapeClosestHit(targets, r, &h, TMIN, TMAX)) {
        Ray r_out;
        Vec3 attenuation;
        if (materialScatter(material[h.material_type], r, &r_out, &h, &attenuation)) {
            Vec3 color = ray_color(&r_out, targets, material, ncollision-1);
            return vec3Product(&attenuation, &color);
        }

        return (Vec3){0.0};
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
    const int w = 700;
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
    ShapeObjectArrayPtr targets = shapeArrayInit(4,
            shapeObjectInit(SPHERE, vec3Create(0.0, -100.5, -1), 100.0), // ground
            shapeObjectInit(SPHERE, vec3Create(0.0, 0.0, -1.0), 0.5),    // center
            shapeObjectInit(SPHERE, vec3Create(-1.0, 0.0, -1.0), 0.5),   // left 
            shapeObjectInit(SPHERE, vec3Create(1.0, 0.0, -1.0), 0.5)     // right
    );

    // Materials
    MaterialPtr mat_array[] = {
        materialInit(LAMBERTIAN, (Vec3) {0.8, 0.8, 0.0}), // ground
        materialInit(LAMBERTIAN, (Vec3) {0.7, 0.3, 0.3}), // center
        materialInit(METAL, (Vec3) {0.8, 0.8, 0.8}),      // right
        materialInit(METAL, (Vec3) {0.8, 0.6, 0.2})       // left
    };

    // Associate materials to objects
    for (int i = 0; i < 4; i++) {
        setMaterial(shapeArrayAt(targets, i), i);
    }
    
    /* Drawing constants */
    const int samples_per_pixel = 50;
    const int max_collisions = 50;

    for(int row = h-1; row >= 0; --row) {
        for(int col = 0; col < w; col++) {
            Vec3 pixel_color = {0};
            
            // Antialising
            for (int s = 0; s < samples_per_pixel; ++s) {
                double u = (double)((double)col + randUniform()) / (w-1);
                double v = (double)((double)row + randUniform()) / (h-1);
                
                Ray r = cameraGetRay(&cam, u, v);

                Vec3 new_color = ray_color(&r, targets, mat_array, max_collisions);
                pixel_color = vec3NSum(2, &pixel_color, &new_color);
            }

            write_color(row, col, pixel_color, samples_per_pixel);
        }
    }

    ppmSaveAs("output/8_metal.ppm");

    ppmDestroy();
    shapeArrayDestroy(targets);
    for(int i = 0; i < 4; i++) {
        materialDestroy(mat_array[i]);
    }
}
