#include "framebuffer.h"

#include <cpu/system.h>
#include <bootloader.h>
#include <utils/printf.h>
#include <utils/ansi.h>

// #define u32BitMask(size,shift) (size == 0 ? 0x00000000 : ((0xffffffff >> (32 - size)) << shift))

Framebuffer fb;

void fb_init() {
   if (bootloader.fb->framebuffer_count <= 0)
      // ... there is no framebuffer sooooo no printing
      panic(null);

   fb.ptr = bootloader.fb->framebuffers[0]->address;
   fb.width = bootloader.fb->framebuffers[0]->width;
   fb.height = bootloader.fb->framebuffers[0]->height;
   fb.pitch = bootloader.fb->framebuffers[0]->pitch;
   fb.bpp = bootloader.fb->framebuffers[0]->bpp;
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
void fb_put_pixel(u32 x, u32 y, u8 r, u8 g, u8 b) {
   u32 where = (x + y * fb.width) * 4;
   fb.ptr[where] = b;
   fb.ptr[where + 1] = g;
   fb.ptr[where + 2] = r;
   fb.ptr[where + 3] = 0;
}

void fb_draw_rect(u32 top, u32 bottom, u32 left, u32 right, u8 r, u8 g, u8 b) {
   // clamp the values
   if (top < 0) top = 0;
   if (bottom > fb.height) bottom = fb.height;
   if (left < 0) left = 0;
   if (right > fb.width) right = fb.width;

   u32 where = (left + top * fb.width) * 4;
   printf_("%d\n", where);
   for (Usize i = top; i < bottom; i++) {
      for (Usize j = left; j < right; j++) {
         // tbh idk why it has to go bgra, is it because of endianness?
         // if someone sees this and knows please tell me
         fb.ptr[where + j * 4] = b;
         fb.ptr[where + j * 4 + 1] = g;
         fb.ptr[where + j * 4 + 2] = r;
         fb.ptr[where + j * 4 + 3] = 0;
      }
      where += fb.pitch;
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
