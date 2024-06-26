#ifndef MOSS_KERN_FRAMEBUFFER_H
#define MOSS_KERN_FRAMEBUFFER_H

#include <limine/limine.h>

typedef struct {
   u32* ptr;
   u32 width;
   u32 height;
   u16 bpp;
   u32 pitch;
   u32 red_mask_size; 
   u32 red_mask_shift;
   u32 green_mask_size;
   u32 green_mask_shift;
   u32 blue_mask_size;
   u32 blue_mask_shift;
} Framebuffer;

extern Framebuffer fb;

void fb_init(); 
void fb_put_pixel(u32 x, u32 y, u8 r, u8 g, u8 b);
void fb_draw_rect(u32 top, u32 bottom, u32 left, u32 right, u8 r, u8 g, u8 b);
// void fb_mode_debug(u32 mode);
// void fb_debug();

#endif // MOSS_KERN_FRAMEBUFFER_H
