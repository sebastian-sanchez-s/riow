#include "lib/ppm.h"

int main() {
    int h = 512;
    int w = 512;

    ppmInit(h, w);
    PPMColor c = {{0}};

    float ri, gi, bi = 0.25;

    for(int row = h-1; row >= 0; row--) {
        for(int col = 0; col < w; col++) {
            ri = (float)col / (w-1);
            gi = (float)row / (h-1);

            c.r = ri * 255;
            c.g = gi * 255;
            c.b = bi * 255;

            ppmSet(row, col, c);
        }
    }

    ppmSaveAs("output/1_space.ppm");
    ppmDestroy();
}
