#ifndef BMP_LIB_H
#define BMP_LIB_H

#include <stddef.h>

void * BMP_malloc(size_t size, const char * msg_failed);

void * BMP_open(const char * filename, const char * mode);

#endif
