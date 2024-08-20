#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdint.h>

// - Structs -
#pragma pack(1)
struct BMP_HEADER {
    uint8_t     magic_num[2]; // "BM"
    uint32_t    file_size;
    uint16_t    reserved;     
    uint16_t    reserved_2;
    uint32_t    offset;     
};

struct DIB_HEADER {
    uint32_t header_size;
    uint32_t width;
    uint32_t height;
    uint16_t color_panes;
    uint16_t num_bits;
    uint32_t comp_scheme;
    uint32_t img_size;
    uint32_t h_resolution;
    uint32_t v_resolution;
    uint32_t num_palette_colors;
    uint32_t num_important_colors;
};

struct Pixel {
    uint8_t r;
    uint8_t g;
    uint8_t b;
};

struct CBM_HEADER {
    uint16_t format_id;
    uint32_t width;
    uint32_t height;
    uint32_t num_palette_colors;
    uint32_t palette_offset;
    uint32_t img_array_offset;
};
#pragma pack(4)

// - Function Decl - 
int cbm_info(int argc, char *argv[]);
int bmp_info(int argc, char *argv[]);


#endif