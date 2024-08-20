#include "common.h"

int bmp_info(int argc, char *argv[]) {
    struct CBM_HEADER cbm_header;
    struct BMP_HEADER bmp_header;
    struct DIB_HEADER dib_header;

    FILE* cbm_file = fopen(argv[2],"rb");
    if(!cbm_file) printf("FNF Error!\n");
    fread(&cbm_header, sizeof(cbm_header), 1, cbm_file);
    
    if (cbm_header.format_id != 0x7449) {
        printf("The format is not supported.\n");
        return false;
    }

    int padding = (4 - (cbm_header.width * 3) % 4) % 4; // calc padding
    int size_no_padding  = (cbm_header.width * cbm_header.height) * 3; // get size times 3 for pixels
    int size_padding = size_no_padding + padding * cbm_header.height;


    // ========== LOAD BMP / DIB HEADER =========== //
    // - BMP -
    bmp_header.magic_num[0] = 'B'; bmp_header.magic_num[1] = 'M';
    bmp_header.file_size = size_padding + sizeof(struct BMP_HEADER)+sizeof(struct DIB_HEADER);
    bmp_header.reserved = 0;
    bmp_header.reserved_2 = 0;
    bmp_header.offset = sizeof(struct BMP_HEADER) + sizeof(struct DIB_HEADER); // size of both headers - BMP and DIB

    // - DIB - 
    dib_header.header_size = sizeof(struct DIB_HEADER);
    dib_header.width = cbm_header.width;
    dib_header.height = cbm_header.height;
    dib_header.color_panes = 1;
    dib_header.num_bits = sizeof(struct Pixel)*8;
    dib_header.comp_scheme = 0;
    dib_header.img_size = 0;
    dib_header.h_resolution = 0;
    dib_header.v_resolution = 0;
    dib_header.num_palette_colors = 0;
    dib_header.num_important_colors = 0;


    //============ PRINT BMP / DIB HEADER ============//
    // - BMP -
    printf("=== BMP Header ===\n");
    printf("Type: %c%c\n", bmp_header.magic_num[0], bmp_header.magic_num[1]);
    printf("Size: %u\n", bmp_header.file_size);
    printf("Reserved 1: %u\n", bmp_header.reserved);
    printf("Reserved 2: %u\n", bmp_header.reserved_2);
    printf("Image offset: %u\n", bmp_header.offset);

    // - DIB -
    printf("\n=== DIB Header ===\n");
    printf("Size: %u\n", dib_header.header_size);
    printf("Width: %u\n", dib_header.width);
    printf("Height: %u\n", dib_header.height);
    printf("# color planes: %u\n", dib_header.color_panes);
    printf("# bits per pixel: %u\n", dib_header.num_bits);
    printf("Compression scheme: %u\n", dib_header.comp_scheme);
    printf("Image size: %u\n", dib_header.img_size);
    printf("Horizontal resolution: %u\n", dib_header.h_resolution);
    printf("Vertical resolution: %u\n", dib_header.v_resolution);
    printf("# colors in palette: %u\n", dib_header.num_palette_colors);
    printf("# important colors: %u\n", dib_header.num_important_colors);

    return false;
}