#ifndef BMP_H
#define BMP_H

#define BMP_SIGNATURE               0x4d42
#define BMP_FILEHEADER_SIZE         14

#include <stdint.h>

#include "BMP_color.h"

enum DIB_TYPES {BITMAPINFOHEADER, BITMAPV5HEADER};

#pragma pack(push, 1)

struct FILEHEADER {
    uint16_t signature; 
    uint32_t file_size; 
    uint16_t reserved1;
    uint16_t reserved2;
    uint32_t offset;                      // where pixel_data begins (fileheader + infoheader)
};

struct BMP {
    struct FILEHEADER * fileheader;
    void * infoheader;                   // DIB it's determinate on creation 
    uint8_t * pixel_data;                // 1-byte pointer arithmetic 
    enum DIB_TYPES dib_type;             // that's why we have a tracker
};

#pragma pack(pop)

/*******************************************
 ************ PRIMITIVE FUNCTIONS **********
 *******************************************/
struct BMP * BMP_read_from_file(const char *); 

uint32_t width_in_bytes(struct BMP * image);

void setup_fileheader(struct BMP * image);

void setup_infoheader(struct BMP * image, int32_t width, int32_t height, uint16_t color_depth);

struct BMP * BMP_create(int32_t width, int32_t height, uint16_t color_depth, enum DIB_TYPES dib_type);

void BMP_save_without_free(struct BMP * image, const char * filename);

void BMP_save(struct BMP * image, const char * filename);

void BMP_set_pixel(struct BMP * image, int row, int col, struct Color color);

void BMP_set_background(struct BMP * image, struct Color color);


/******************************************
 ******** SETTERS AND GETTERS**************
 ******************************************/

int32_t BMP_get_infoheader_size(struct BMP * image);

void BMP_set_width(struct BMP * image, int32_t width);

uint32_t BMP_get_width(struct BMP * image);

void BMP_set_height(struct BMP * image, int32_t height);

uint32_t BMP_get_height(struct BMP * image);

void BMP_set_color_planes(struct BMP * image, uint16_t planes);

uint16_t BMP_get_color_planes(struct BMP * image);

void BMP_set_color_depth(struct BMP * image, uint16_t depth);

uint16_t BMP_get_color_depth(struct BMP * image);

void BMP_set_image_size(struct BMP * image, uint32_t size);

uint32_t BMP_get_image_size(struct BMP * image);

#endif
