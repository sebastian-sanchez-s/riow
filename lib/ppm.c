/* Writes a ppm image with 255 max color */
#include "ppm.h"
#include <stdbool.h>

/*****
 * Globals and macros
 * *********/
PPMObject *focus= NULL;

static inline bool BETWEEN(int value, int lim_inf, int lim_sup) {
    return (value >= lim_inf && value < lim_sup);
}

#define PPM_COORDINATES_SANITY_CHECK(y, x) do {\
    y = (y < 0) ? focus->h + y: y;\
    x = (x < 0) ? focus->w + x: x;\
    dv_true_or_panik(BETWEEN(x, 0, focus->w), "'x' component out of bounds [x:%i]",, x);\
    dv_true_or_panik(BETWEEN(y, 0, focus->h), "'y' component out of bounds [y:%i]",, y);\
} while(0)

#define offset(i, j) (i * 3 * focus->w + 3 * j)

/******
 * Implementations
 * ***********/
PPMObjectPtr ppmInit(int h, int w) {
    focus = dv_malloc(sizeof(*focus));
    focus->w = w;
    focus->h = h;
    focus->pixels = dv_malloc(3 * focus->w * focus->h);
    
    return focus;
}

void ppmSetFocus(PPMObjectPtr new_focus) {
    focus = new_focus;
}

PPMObjectPtr ppmGetFocus() {
    return focus;
}

void ppmDestroy() {
    free(focus->pixels);
    free(focus);
}


void ppmSet(int y, int x, PPMColor c) {
    PPM_COORDINATES_SANITY_CHECK(y, x);

    focus->pixels[offset(y, x)] = c.r;
    focus->pixels[offset(y, x) + 1] = c.g;
    focus->pixels[offset(y, x) + 2] = c.b;
}

void ppmSaveAs(const char * filename) {
    FILE * fd = dv_file_open(filename, "w");

    ppmSave(fd);
    
    fclose(fd);
}

void ppmSave(FILE * fd) {
    fprintf(fd, "P3\n%i %i\n255\n", focus->w, focus->h);
    for (int i = focus->h - 1; i >= 0; i--) {
        for (int j = 0; j < focus->w; j++) {
            fprintf(fd, "%i %i %i ", 
                    focus->pixels[offset(i, j)], 
                    focus->pixels[offset(i, j) + 1],
                    focus->pixels[offset(i, j) + 2]);
        }
        fprintf(fd, "\n");
    }
}
