#include "common.h"

int cbm_info(int argc, char *argv[]) {

    struct CBM_HEADER cbm_header;
    struct Pixel pixel;

    // =============== READ CBM HEADER =============== //
    FILE* cbm_file = fopen(argv[2],"rb");
    if(!cbm_file) printf("FNF Error!\n");
    fread(&cbm_header, sizeof(cbm_header), 1, cbm_file);

    if (cbm_header.format_id != 0x7449) {
        printf("The format is not supported.\n");
        return false;
    }

    //============== PRINT CBM HEADER & PALETTE ==============//
    // - Print CBM H -
    printf("=== CBM Header ===\n");
    printf("Magic: 0x%x\n", cbm_header.format_id);
    printf("Width: %u\n", cbm_header.width);
    printf("Height: %u\n", cbm_header.height);
    printf("Number of Colors: %u\n", cbm_header.num_palette_colors);
    printf("Color Array Offset: %u\n", cbm_header.palette_offset);
    printf("Image Array Offset: %u\n\n", cbm_header.img_array_offset);

    // - Palette -
    printf("=== Palette (R, G, B) ===\n"); 
    for (int i = 0; i < cbm_header.num_palette_colors; i++) {
        fread(&pixel, sizeof(struct Pixel), 1, cbm_file);
        printf("Color %i: (%u, %u, %u)\n", i, pixel.r, pixel.g, pixel.b);
    }

    fclose(cbm_file);
    return false;
}