#include "dasvaca.h"

/**************************
 * STDLIB Common wrappers
 * -- DasVaca --
 *************************/

void * dv_realloc(void *ptr, int size) {
    dv_true_or_panik((size > 0),"'size' is negative [size:%i]",, size);

    void * m = realloc(ptr, size);

    dv_true_or_panik((m != NULL), "Couldn't get memory");

    return m;
}

void * dv_malloc(int size) {
    return dv_realloc(NULL, size);
}


/*************
 * FILE RELATED
 * ***************/

FILE * dv_file_open(const char *filename, const char * mode) {
    FILE *fd = fopen(filename, mode);

    dv_true_or_panik((fd != NULL), "failed at opening file");

    return fd;
}
