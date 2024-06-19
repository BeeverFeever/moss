#ifndef MOSS_KERN_BOOTLOADER_H
#define MOSS_KERN_BOOTLOADER_H

#include <limine/limine.h>

typedef struct {
   volatile struct limine_framebuffer_response* framebuffer;
   volatile struct limine_hhdm_response* hhdm;
   volatile struct limine_kernel_address_response* kernel_address;
   volatile struct limine_memmap_response* memmap;
} Bootloader;

Bootloader bootloader;

void bootloader_init(void);

#endif // MOSS_KERN_BOOTLOADER_H
