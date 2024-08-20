#include "common.h"

int main(int argc, char *argv[]) {
    if(argc < 2) { 
        printf("Not enough parameters.\n");
        return false;
    }
    
    if(!strcmp("--info", argv[1])) {
        cbm_info(argc, argv);
        return false;
    }
        
    if(!strcmp("--bmp-info", argv[1])) {
        bmp_info(argc, argv);
        return false;
    }

    if(!strcmp("--convert", argv[1])) {
        struct CBM_HEADER cbm_header;
        struct Pixel pixel;
        struct BMP_HEADER bmp_header;
        struct DIB_HEADER dib_header;

        // ========== LOAD BMP / DIB HEADER =========== //
        FILE* cbm_file = fopen(argv[2],"rb");
        fread(&cbm_header, sizeof(cbm_header), 1, cbm_file);
        
        // - BMP -
        bmp_header.magic_num[0] = 'B'; bmp_header.magic_num[1] = 'M';
        bmp_header.file_size = (cbm_header.width+(cbm_header.width%4))*cbm_header.height*3 + sizeof(struct BMP_HEADER)+sizeof(struct DIB_HEADER);
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

        // =========== CONVERT BMP ============== //

        // - Load Palette -
        struct Pixel palette_array[cbm_header.num_palette_colors]; 

        for (int i = 0; i < cbm_header.num_palette_colors; i++) {
            fread(&pixel, sizeof(struct Pixel), 1, cbm_file);
            palette_array[i] = pixel;
        }

        // - Variable Declarations -
        int line = cbm_header.img_array_offset + cbm_header.width*(cbm_header.height-1);
        int padding = (4 -(dib_header.width*3) % 4 ) % 4;
        unsigned char index = 0;
        unsigned char paddingByte = 0;
        struct Pixel newPixel;

        // - Write BMP & DIB Headers - 
        FILE* bmp_file = fopen(argv[3], "wb");
        fwrite(&bmp_header, sizeof(bmp_header), 1, bmp_file);
        fwrite(&dib_header, sizeof(dib_header), 1, bmp_file);


        // - Read CBM Index, Write Pixel From Palette - 
        for (int h = 0; h < cbm_header.height; h++) {
            fseek(cbm_file, line, SEEK_SET);
            for (int w = 0; w < cbm_header.width; w++) {

                if (fread(&index, sizeof(char), 1, cbm_file)) {
                    newPixel.r = palette_array[index].b;
                    newPixel.g = palette_array[index].g;
                    newPixel.b = palette_array[index].r; 
                    fwrite(&newPixel, sizeof(newPixel), 1, bmp_file);
                }
            }

            fwrite(&paddingByte, 1, padding, bmp_file);
            line -= cbm_header.width;   // move up a line
        }

        fclose(cbm_file);
        fclose(bmp_file);
    }

    return false;
}