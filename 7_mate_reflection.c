#include "BMP.h"
#include "vector.h"
#include "ray.h"
#include "sphere.h"
#include "camera.h"
#include "random.h"

#include <stdio.h>
#include <stdbool.h>
#include <math.h>

#define TMAX 1000.0
#define TMIN 0.01

typedef struct BMP* Img;

V3 V3_random_in_unit_sphere() {
    float theta = rand_between(0, 6.28);
    float phi = rand_between(0, 3.14);

    return V3_create(sin(phi)*cos(theta), sin(phi)*sin(theta), cos(phi));
}


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


V3 ray_color(Ray_ptr r, Sphere_ptr s[], int ncollision) {
    if (ncollision <= 0) {
        return V3_create(0, 0, 0);
    }

    HitRecord h;
    if (sphere_closest_hit(s, r, &h, TMIN, TMAX)) {
        V3 unit = V3_random_in_unit_sphere();
        unit = V3_scale(&unit, V3_dot(&unit, &h.normal) > 0.0 ? 1.0: -1.0);

        V3 target = V3_nsum(2, &h.point, &unit);

        r->orig = h.point;
        r->dir  = V3_nsum(2, &target, &unit);
        
        V3 color = ray_color(r, s, ncollision - 1);

        return V3_scale(&color, 0.5);
    }

    V3 unit_dir = V3_unit(&r->dir);
    double t = 0.5 * (unit_dir.y + 1.0);

    return V3_create(1.0 - 0.5*t, 1.0 - 0.3*t, 1.0);
}

void write_color(struct BMP* image, int row, int col, V3 pixel_color, int samples_per_pixel) {
    double scale = 1.0/samples_per_pixel;

    pixel_color = V3_scale(&pixel_color, scale);
    pixel_color.x = sqrt(pixel_color.x);
    pixel_color.y = sqrt(pixel_color.y);
    pixel_color.z = sqrt(pixel_color.z);

    struct Color color = {
        .red   = pixel_color.x * MAX_COLOR_24,
        .green = pixel_color.y * MAX_COLOR_24,
        .blue  = pixel_color.z * MAX_COLOR_24
    };

    BMP_set_pixel(image, row, col, color);
}

int main() {
    /* Image */
    const double aspect_ratio = 16.0/9.0;
    const int w = 400;
    const int h = w/aspect_ratio;
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
    Sphere s1 = {
        .center = {0, 0, -1},
        .rad    = 0.5
    };

    Sphere s2 = {
        .center = {0, -100.5, -1},
        .rad    = 100
    };

    Sphere_ptr spheres[] = {&s1, &s2, NULL};
    
    /* Drawing constants */
    const int samples_per_pixel = 50;
    const int max_collisions = 25;

    for(int row = h-1; row >= 0; --row) {
        for(int col = 0; col < w; col++) {
            printf("\r(%3.1f\%) Processing pixel [%5d, %5d]", (1.0-(float)(row*w)/(w*h))*100.0, row, col);
            fflush(stdin);

            V3 pixel_color = {0};
            
            // Antialising
            for (int s = 0; s < samples_per_pixel; ++s) {
                double u = (double)((double)col + uniform()) / (w-1);
                double v = (double)((double)row + uniform()) / (h-1);
                
                Ray r = Camera_get_ray(&cam, u, v);

                V3 new_color = ray_color(&r, spheres, max_collisions);
                pixel_color = V3_nsum(2, &pixel_color, &new_color);
            }

            write_color(image, row, col, pixel_color, samples_per_pixel);
        }
    }

    BMP_save(image, "output/7_mate_reflection.bmp");
}
