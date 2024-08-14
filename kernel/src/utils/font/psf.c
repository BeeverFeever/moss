#include "psf.h"
#include <utils/printf.h>

// int init_psf1(Psf1Header* header) {
//    header->magic[0];
// }

int init_psf2(Psf2Header* header) {
   header->magic[0] = zap_ext_light20[0];
   header->magic[1] = zap_ext_light20[1];
   header->magic[2] = zap_ext_light20[2];
   header->magic[3] = zap_ext_light20[3];
   if (header->magic != (Byte[4]){PSF2_HEADER0, PSF2_HEADER1, PSF2_HEADER2, PSF2_HEADER3}) {
      printf_("[psf font] Provided font not psf2, only psf2 supported.");
      return -1;
   }

   return 0;
}
