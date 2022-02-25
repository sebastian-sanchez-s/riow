#ifndef _DV_DASVACA_
#define _DV_DASVACA_
/**************************************
 *  Collection of common shortcuts and macros
 *  I use often.
 *  --- DasVaca ---
 *************************************/
#include <stdio.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdlib.h>

/********************
 * Types shortcuts
 * -- DasVaca --
 *******************/

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;

typedef int8_t i8;
typedef int16_t i16;
typedef int32_t i32;

/*******************
 * Error Macros
 * -- DasVaca --
 ******************/
#define dv_panik(err_msg, ...) do {\
    fprintf(stderr,\
"\n[DV_PANIK]\n\
File     => %s\n\
Location => %s:%i\n\
Error    => ",\
            __FILE__,\
            __func__,\
            __LINE__);\
    fprintf(stderr, err_msg"\n\n" __VA_ARGS__);\
    exit(-1);\
} while(0) 

#define dv_true_or_panik(is_valid, err_msg, ...) do {\
    if (!is_valid) { dv_panik(err_msg, __VA_ARGS__); } \
} while(0)


/**************************
 * Interfaces 
 * -- DasVaca --
 *************************/
void * dv_realloc(void *ptr, int size);
void * dv_malloc(int size);
FILE * dv_file_open(const char *filename, const char * mode);

#endif
