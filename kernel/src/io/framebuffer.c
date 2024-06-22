#include "framebuffer.h"

#include <cpu/system.h>
#include <bootloader.h>
#include <utils/printf.h>

#define RGB_TO_32(r,g,b) ()

void fb_init() {
   if (bootloader.fb->framebuffer_count <= 0)
      // ... there is no framebuffer sooooo no printing
      panic(null);

   fb = bootloader.fb->framebuffers[0];
}

void fb_debug() {
   printf_("Framebuffer info:\n");
   printf_("width: %lu\n", fb->width);
   printf_("height: %lu\n", fb->height);
   printf_("pitch: %lu\n", fb->pitch);
   printf_("bpp: %hd\n", fb->bpp);
   printf_("mem model: %d %0#8x\n", fb->memory_model, fb->memory_model);
   printf_("MASKS size shift\n");
   printf_("red mask: %d %d\n", fb->red_mask_size, fb->red_mask_shift);
   printf_("green mask: %d %d\n", fb->green_mask_size, fb->green_mask_shift);
   printf_("blue mask: %d %d\n", fb->blue_mask_size, fb->blue_mask_shift);
}

// inline void fb_put_pixel(u32 x, u32 y, Colour col) {
//    fb->address[y * fb->width * fb->bpp + x] = 0x00ff0000 & col.r;
// }
