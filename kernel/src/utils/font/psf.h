#ifndef MOSS_KERN_PSF_H
#define MOSS_KERN_PSF_H

#include "zap-ext-light20.h"
// #include <utils/printf.h>

#define PSF1_HEADER0 0x36
#define PSF1_HEADER1 0x04

typedef struct {
   u8 magic[2];
   u8 font_mode;
   u8 char_size;
} Psf1Header;

int init_psf1(Psf1Header* header);

#define PSF2_HEADER0 (Byte)0x72
#define PSF2_HEADER1 (Byte)0xb5
#define PSF2_HEADER2 (Byte)0x4a
#define PSF2_HEADER3 (Byte)0x86

typedef struct {
   Byte magic[4];
   u32 version;
   u32 header_size;
   u32 flags;
   u32 length;   // number of glyphs
   u32 charsize; // bytes per character
   // max dimensions of glyphs
   u32 char_height;
   u32 char_width;
} Psf2Header;

// int init_psf2(Psf2Header* header) {
//    header->magic[0] = zap_ext_light20[0];
//    header->magic[1] = zap_ext_light20[1];
//    header->magic[2] = zap_ext_light20[2];
//    header->magic[3] = zap_ext_light20[3];
//    if (header->magic != (Byte[4]){PSF2_HEADER0, PSF2_HEADER1, PSF2_HEADER2, PSF2_HEADER3}) {
//       // printf_("[psf font] Provided font not psf2, only psf2 supported.");
//       return -1;
//    }
//
//
// }

#endif // MOSS_KERN_PSF_H
