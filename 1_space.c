#include "BMP.h"

int main() {
    int h = 512;
    int w = 512;

    struct BMP * image = BMP_create(w, h, 24, 0);
    struct Color color = {0};
    float ri, gi, bi = 0.25;

    for(int row = h-1; row >= 0; row--) {
        for(int col = 0; col < w; col++) {
            ri = (float)col / (w-1);
            gi = (float)row / (h-1);

            color.red = ri * MAX_COLOR_24;
            color.green = gi * MAX_COLOR_24;
            color.blue = bi * MAX_COLOR_24;

            BMP_set_pixel(image, row, col, color);
        }
    }

    BMP_save(image, "output/1_space.bmp");
}
