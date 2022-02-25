#include "lib/ppm.h"

typedef union PPM_Color COLOR;

int main() {
    int h = 512;
    int w = 512;

    PPM_init(h, w);
    COLOR c = {{0}};

    float ri, gi, bi = 0.25;

    for(int row = h-1; row >= 0; row--) {
        for(int col = 0; col < w; col++) {
            ri = (float)col / (w-1);
            gi = (float)row / (h-1);

            c.r = ri * 255;
            c.g = gi * 255;
            c.b = bi * 255;

            PPM_set(row, col, c);
        }
    }

    PPM_save_as("output/1_space.ppm");
    PPM_destroy();
}
