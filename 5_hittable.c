#include "BMP.h"
#include "vector.h"
#include "ray.h"
#include "sphere.h"

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

struct Color ray_color(Ray_ptr r, Sphere_ptr s[]) {
    HitRecord h;

    if (sphere_closest_hit(s, r, &h, 0, 500)) {
        struct Color color = {
            .red   = .5*(h.normal.x+1.0)*MAX_COLOR_24,
            .green = .5*(h.normal.y+1.0)*MAX_COLOR_24,
            .blue  = .5*(h.normal.z+1.0)*MAX_COLOR_24
        };
        return color;
    }

    V3 unit_dir = V3_unit(&r->dir);
    double t = 0.5 * (unit_dir.y + 1.0);

    struct Color color = {
        .red  = (1.0 - 0.5*t) * MAX_COLOR_24,
        .green= (1.0 - 0.3*t) * MAX_COLOR_24,
        .blue = MAX_COLOR_24
    };

    return color;
}

int main() {
    /* Image */
    double aspect_ratio = 16.0/9.0;
    int w = 400;
    int h = w/aspect_ratio;
    Img image = BMP_create(w, h, 24, 0);
    
    double vw_h = 2.0;
    double vw_w = round(vw_h * aspect_ratio);
    double focal_length = 1.0;
    
    /* Camera */
    V3 direction;
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
    Ray ray = {.orig = origin, .dir = direction};

    Sphere s1 = {
        .center = V3_create(0, 0, -1),
        .rad    = 0.5
    };

    Sphere s2 = {
        .center = V3_create(0, -100.5, -1),
        .rad    = 100
    };

    Sphere_ptr spheres[] = {&s1, &s2, NULL};

    for(int row = h-1; row >= 0; --row) {
        for(int col = 0; col < w; col++) {
            double u = (double)col / (w-1);
            double v = (double)row / (h-1);

            V3 scale_h = V3_scale(&horizontal, u);
            V3 scale_v = V3_scale(&vertical, v);

            ray.dir = V3_sum(&llc, &scale_h, &scale_v, NULL);
            
            struct Color color = ray_color(&ray, spheres);
            BMP_set_pixel(image, row, col, color);
        }
    }

    BMP_save(image, "output/5_hittable.bmp");
}
