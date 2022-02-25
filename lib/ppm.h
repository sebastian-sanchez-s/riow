#ifndef _PPM_
#define _PPM_

#include "dasvaca.h"

struct PPM {
    int w;
    int h;
    u8 * pixels;
};

union PPM_Color {
    struct {u8 r, g, b; };
    u32 color;
};

struct PPM * PPM_init(int h, int w);
void PPM_destroy();

void PPM_set_focus(struct PPM *);
struct PPM * PPM_get_focus();

void PPM_set(int y, int x, union PPM_Color);

void PPM_save_as(const char *);
void PPM_save(FILE *);

#endif
