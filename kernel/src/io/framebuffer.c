#include "framebuffer.h"

#include <cpu/system.h>
#include <bootloader.h>
#include <utils/printf.h>
#include <utils/ansi.h>

#define u32BitMask(size,shift) (size == 0 ? 0x00000000 : ((0xffffffff >> (32 - size)) << shift))
#define fbAlphaMask ()

// clamps including min and max
// static void inline clamp(u32* value, u32 min, u32 max) {
//    *value = *value < min ? min : *value;
//    *value = *value > max ? max : *value;
// }

Framebuffer fb = {0};

void fb_init() {
   if (bootloader.fb->framebuffer_count <= 0)
      // ... there is no framebuffer sooooo no printing
      panic(null);

   fb.ptr = (u32*)bootloader.fb->framebuffers[0]->address;
   fb.width = bootloader.fb->framebuffers[0]->width;
   fb.height = bootloader.fb->framebuffers[0]->height;
   fb.pitch = bootloader.fb->framebuffers[0]->pitch;
   fb.bpp = bootloader.fb->framebuffers[0]->bpp;
   fb.Bpp = fb.bpp / 8;
   fb.red_mask_size = bootloader.fb->framebuffers[0]->red_mask_size;
   fb.red_mask_shift = bootloader.fb->framebuffers[0]->red_mask_shift;
   fb.green_mask_size = bootloader.fb->framebuffers[0]->green_mask_size;
   fb.green_mask_shift = bootloader.fb->framebuffers[0]->green_mask_shift;
   fb.blue_mask_size = bootloader.fb->framebuffers[0]->blue_mask_size;
   fb.blue_mask_shift = bootloader.fb->framebuffers[0]->blue_mask_shift;
}

// IMPORTANT: This function should not be used in a massive/important loop.
// Calculating where each itteration will slow it down considerably,
// instead refer to fb_draw_rect for what to do.
void fb_put_pixel(u32 x, u32 y, u32 col) {
   if (x < fb.width && y < fb.height) {
      u32 where = x + y * fb.width;
      fb.ptr[where] = col;
   }
}

void fb_draw_rect(u32 x, u32 y, u32 width, u32 height, u32 col) {
   // cases where we can't draw anything so just return
   // if (y > fb.height || x > fb.width) return;
   // if (width > fb.width || height > fb.height) return;

   if (y < 0) y = 0;
   if (x < 0) x = 0;
   if (x + width > fb.width) width = fb.width - x;
   if (y + height > fb.height) height = fb.height - y;

   u32 offset = x + y * fb.width;
   for (Size row = y; row < height; row++) {
      for (Size column = x; column < width + x; column++) {
         fb.ptr[offset + column] = col;
      }
      offset += fb.width;
   }
}

// void fb_debug() {
//    printf_("Framebuffer info:\n");
//    printf_("width: %lu\n", fb->width);
//    printf_("height: %lu\n", fb->height);
//    printf_("pitch: %lu\n", fb->pitch);
//    printf_("bpp: %hd\n", fb->bpp);
//    printf_("mem model: %d %0#8x\n", fb->memory_model, fb->memory_model);
//    printf_("mode count: %lu\n", fb->mode_count);
//    printf_("MASKS size shift\n");
//
//    printf_(colour(FG_RED) "red: %d %d %0#10x\n" reset(R_ALL), 
//          fb->red_mask_size,   
//          fb->red_mask_shift, 
//          fbU32BitMask(fb->red_mask_size, fb->red_mask_shift));
//
//    printf_(colour(FG_GREEN) "green: %d %d %0#10x\n" reset(R_ALL), 
//          fb->green_mask_size, 
//          fb->green_mask_shift, 
//          fbU32BitMask(fb->green_mask_size, fb->green_mask_shift));
//
//    printf_(colour(FG_BLUE) "blue: %d %d %0#10x\n" reset(R_ALL), 
//          fb->blue_mask_size,  
//          fb->blue_mask_shift, 
//          fbU32BitMask(fb->blue_mask_size, fb->blue_mask_shift));
// }
//
// void fb_mode_debug(u32 mode) {
//    printf_("Framebuffer mode %d\n", mode); 
//    printf_("width: %lu\n", fb->modes[mode]->width);
//    printf_("height: %lu\n", fb->modes[mode]->height);
//    printf_("pitch: %lu\n", fb->modes[mode]->pitch);
//    printf_("bpp: %hd\n", fb->modes[mode]->bpp);
//    printf_("mem model: %d %0#8x\n", fb->modes[mode]->memory_model, fb->modes[mode]->memory_model);
//    printf_("MASKS size shift\n");
//
//    printf_(colour(FG_RED) "red: %d %d %0#10x\n" reset(R_ALL), 
//          fb->modes[mode]->red_mask_size,   
//          fb->modes[mode]->red_mask_shift, 
//          fbU32BitMask(fb->modes[mode]->red_mask_size, fb->modes[mode]->red_mask_shift));
//
//    printf_(colour(FG_GREEN) "green: %d %d %0#10x\n" reset(R_ALL), 
//          fb->modes[mode]->green_mask_size, 
//          fb->modes[mode]->green_mask_shift, 
//          fbU32BitMask(fb->modes[mode]->green_mask_size, fb->modes[mode]->green_mask_shift));
//
//    printf_(colour(FG_BLUE) "blue: %d %d %0#10x\n" reset(R_ALL), 
//          fb->modes[mode]->blue_mask_size,  
//          fb->modes[mode]->blue_mask_shift, 
//          fbU32BitMask(fb->modes[mode]->blue_mask_size, fb->modes[mode]->blue_mask_shift));
// }
//
