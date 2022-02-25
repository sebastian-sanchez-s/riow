/* Writes a ppm image with 255 max color */
#include "ppm.h"
#include <stdbool.h>

typedef struct PPM IMG;
typedef union PPM_Color COLOR;

/*****
 * Globals and macros
 * *********/
IMG *focus= NULL;

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
IMG* PPM_init(int h, int w) {
    focus = dv_malloc(sizeof(*focus));
    focus->w = w;
    focus->h = h;
    focus->pixels = dv_malloc(3 * focus->w * focus->h);
    
    return focus;
}

void PPM_set_focus(IMG *new_focus) {
    focus = new_focus;
}

void PPM_destroy() {
    free(focus->pixels);
    free(focus);
}


void PPM_set(int y, int x, COLOR c) {
    PPM_COORDINATES_SANITY_CHECK(y, x);

    focus->pixels[offset(y, x)] = c.r;
    focus->pixels[offset(y, x) + 1] = c.g;
    focus->pixels[offset(y, x) + 2] = c.b;
}

void PPM_save_as(const char * filename) {
    FILE * fd = dv_file_open(filename, "w");

    PPM_save(fd);
    
    fclose(fd);
}

void PPM_save(FILE * fd) {
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
