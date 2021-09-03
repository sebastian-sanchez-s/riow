#include "BMP.h"
#include "vector.h"
#include "ray.h"
#include <stdio.h>
#include <stdbool.h>
#include <math.h>

typedef struct BMP* Img;

double hit_sphere(V3_ptr center, double rad, Ray_ptr ray) {
    V3 minus_center = V3_scale(center, -1);
    V3 oc = V3_sum(&ray->orig, &minus_center, NULL);

    double a  = V3_dot(&ray->dir, &ray->dir);
    double hb = V3_dot(&oc, &ray->dir);
    double c  = V3_dot(&oc, &oc) - rad*rad;

    double discriminant = hb*hb - a*c;
    
    return discriminant >= 0.0 ? (-hb - sqrt(discriminant))/a: -1.0;
}


struct Color ray_color(Ray_ptr r) {
    V3 center = {.x = 0, .y = 0, .z = -1};

    double t = hit_sphere(&center, 0.5, r);

    if (t > 0.0) {
        V3 ray_at = Ray_at(r, t);
        V3 minus_center = V3_scale(&center, -1.0);
        V3 normal = V3_sum(&ray_at, &minus_center, NULL);
        V3 unit_normal = V3_unit(&normal);

        /* -1 <= unit        <= 1
         *  0 <= unit+1      <= 2
         *  0 <= .5*(unit+1) <= 1 */
        struct Color color = {
            .red   = .5*(unit_normal.x+1.0)*MAX_COLOR_24,
            .green = .5*(unit_normal.y+1.0)*MAX_COLOR_24,
            .blue  = .5*(unit_normal.z+1.0)*MAX_COLOR_24
        };
        return color;
    }

    V3 unit_dir = V3_unit(&r->dir);
    t = 0.5 * (unit_dir.y + 1.0);

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
    Ray ray = {.orig = origin, .dir = direction};

    for(int row = h-1; row >= 0; --row) {
        for(int col = 0; col < w; col++) {
            double u = (double)col / (w-1);
            double v = (double)row / (h-1);

            V3 scale_h = V3_scale(&horizontal, u);
            V3 scale_v = V3_scale(&vertical, v);

            ray.dir = V3_sum(&llc, &scale_h, &scale_v, NULL);
            
            struct Color color = ray_color(&ray);
            BMP_set_pixel(image, row, col, color);
        }
    }

    BMP_save(image, "output/4_shading.bmp");
}
