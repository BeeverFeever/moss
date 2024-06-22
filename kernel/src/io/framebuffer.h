#ifndef MOSS_KERN_FRAMEBUFFER_H
#define MOSS_KERN_FRAMEBUFFER_H

#include <limine/limine.h>

volatile struct limine_framebuffer* fb;

typedef struct {
   u8 r; 
   u8 g; 
   u8 b;
} Colour;

void fb_init(); 
void fb_put_pixel(u32 x, u32 y, Colour col);
void fb_debug();

#endif // MOSS_KERN_FRAMEBUFFER_H
