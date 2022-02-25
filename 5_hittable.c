#include "lib/ppm.h"
#include "lib/vector.h"
#include "lib/ray.h"
#include "lib/sphere.h"

#include <stdio.h>
#include <stdbool.h>
#include <math.h>

#define MAX_COLOR 255

typedef union PPM_Color Color; 

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

Color ray_color(Ray_ptr r, Sphere_ptr s[]) {
    HitRecord h;

    if (sphere_closest_hit(s, r, &h, 0, 500)) {
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

    Sphere s1 = {
        .center = V3_create(0, 0, -1),
        .rad    = 0.5
    };

    Sphere s2 = {
        .center = V3_create(0, -100.5, -1),
        .rad    = 100
    };

    Sphere_ptr spheres[] = {&s1, &s2, NULL};

    for(int row = 0; row < h; row++) {
        for(int col = 0; col < w; col++) {
            double u = (double)col / (w-1);
            double v = (double)row / (h-1);

            V3 scale_h = V3_scale(&horizontal, u);
            V3 scale_v = V3_scale(&vertical, v);

            ray.dir = V3_nsum(3, &llc, &scale_h, &scale_v);
            
            Color color = ray_color(&ray, spheres);
            PPM_set(row, col, color);
        }
    }

    PPM_save_as("output/5_hittable.ppm");
}
