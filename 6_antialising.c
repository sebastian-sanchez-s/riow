#include "BMP.h"
#include "vector.h"
#include "ray.h"
#include "sphere.h"
#include "camera.h"
#include "random.h"

#include <stdio.h>
#include <stdbool.h>
#include <math.h>

typedef struct BMP* Img;

bool sphere_closest_hit(Sphere_ptr s[], Ray_ptr r, HitRecord_ptr h, double t_min, double t_max) {
    HitRecord ch; // current hit record
    bool has_hitted = false;
    double closest_hit = t_max;

    for (int i = 0; s[i]; i++) {
        if (Sphere_hit(s[i], r, &ch, t_min, closest_hit)) {
            has_hitted = true;
            closest_hit = ch.t;
            *h = ch;
        }
    }

    return has_hitted;
}

V3 ray_color(Ray_ptr r, Sphere_ptr s[]) {
    HitRecord h;

    if (sphere_closest_hit(s, r, &h, 0, 500)) {
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

void write_color(struct BMP* image, int row, int col, V3 pixel_color, int samples_per_pixel) {
    double scale = 1.0/samples_per_pixel;

    pixel_color = V3_scale(&pixel_color, scale);

    struct Color color = {
        .red   = pixel_color.x * MAX_COLOR_24,
        .green = pixel_color.y * MAX_COLOR_24,
        .blue  = pixel_color.z * MAX_COLOR_24
    };

    BMP_set_pixel(image, row, col, color);
}

int main() {
    /* Image */
    double aspect_ratio = 16.0/9.0;
    int w = 400;
    int h = w/aspect_ratio;
    int samples_per_pixel = 100;
    Img image = BMP_create(w, h, 24, 0);
    
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
    Sphere s1 = {
        .center = {0, 0, -1},
        .rad    = 0.5
    };

    Sphere s2 = {
        .center = {0, -100.5, -1},
        .rad    = 100
    };

    Sphere_ptr spheres[] = {&s1, &s2, NULL};

    for(int row = h-1; row >= 0; --row) {
        for(int col = 0; col < w; col++) {
            V3 pixel_color = {0};
            
            // Antialising
            for (int s = 0; s < samples_per_pixel; ++s) {
                double u = (double)((double)col + uniform()) / (w-1);
                double v = (double)((double)row + uniform()) / (h-1);
                
                Ray r = Camera_get_ray(&cam, u, v);

                V3 new_color = ray_color(&r, spheres);
                pixel_color = V3_sum(&pixel_color, &new_color, NULL);
            }
            
            write_color(image, row, col, pixel_color, samples_per_pixel);
        }
    }

    BMP_save(image, "output/6_antialiasing.bmp");
}
