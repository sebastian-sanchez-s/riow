#ifndef _PPM_
#define _PPM_

#include "dasvaca.h"

typedef struct {
    int w;
    int h;
    u8 * pixels;
} PPMObject;

typedef PPMObject* PPMObjectPtr;

typedef union {
    struct {u8 r, g, b; };
    u32 color;
} PPMColor;

PPMObjectPtr ppmInit(int h, int w);
void ppmDestroy();

void ppmSetFocus(PPMObject*);
PPMObjectPtr ppmGetFocus();

void ppmSet(int y, int x, PPMColor);

void ppmSaveAs(const char *);
void ppmSave(FILE *);

#endif
