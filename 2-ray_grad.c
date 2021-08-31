#include "BMP.h"
#include "vector.h"
#include "ray.h"
#include <stdio.h>

int main() {
    /* Constants */
    const double epsilon = 1e-3;

    /* Image */
    double aspect_ratio = 16.0/9.0;
    int w = 400;
    int h = w/aspect_ratio;
    struct BMP * image = BMP_create(w, h, 24, 0);
    
    int vw_h = 2;
    int vw_w = vw_h * aspect_ratio;
    int focal_length = 1;
    
    /* Camera */
    struct Vector3 direction, origin = {0};
    struct Vector3 horizontal = {.x = vw_w, .y = 0   , .z = 0};
    struct Vector3 vertical   = {.x = 0   , .y = vw_h, .z = 0};
    struct Vector3 llc = { // lower left corner
        .x = origin.x - horizontal.x/2 - vertical.x/2,
        .y = origin.y - horizontal.y/2 - vertical.y/2,
        .z = origin.z - horizontal.z/2 - vertical.z/2 - focal_length
    };
    
    /* Drawing/render */
    struct Ray ray = {0};
    struct Vector3 unit = {0};
    struct Color color = {.red = 0, .green = 0, .blue = MAX_COLOR_24};

    ray.origin = &origin;
    ray.direction = &direction;
    for(int row = h-1; row >= 0; --row) {
        for(int col = 0; col < w; col++) {
            double u = (double)col / (w-1);
            double v = (double)row / (h-1);

            ray.direction->x = llc.x + u*horizontal.x + v*vertical.x;
            ray.direction->y = llc.y + u*horizontal.y + v*vertical.y;
            ray.direction->z = llc.z + u*horizontal.z + v*vertical.z;

            ray.direction->x = ray.direction->x < epsilon ? epsilon: ray.direction->x;
            ray.direction->y = ray.direction->y < epsilon ? epsilon: ray.direction->y;
            ray.direction->z = ray.direction->z < epsilon ? epsilon: ray.direction->z;
            
            V3_unit(&unit, ray.direction);
            double t = 0.5*(unit.y + 1.0);

            color.red = (1.0-t)*MAX_COLOR_24 + t*MAX_COLOR_24*0.5;
            color.green= (1.0-t)*MAX_COLOR_24 + t*MAX_COLOR_24*0.7;

            BMP_set_pixel(image, row, col, color);
        }
    }

    BMP_save(image, "output/2-ray_gradient.bmp");
}
