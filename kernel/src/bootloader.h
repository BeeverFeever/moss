#ifndef MOSS_KERN_BOOTLOADER_H
#define MOSS_KERN_BOOTLOADER_H

#include <limine/limine.h>

typedef struct {
   
} Bootloader;

#define bootloader_module(name) extern volatile struct limine_##name##_response* bootloader_##name

bootloader_module(hhdm);
bootloader_module(kernel_address);
bootloader_module(framebuffer);
bootloader_module(memmap);

#undef bootloader_module

void bootloader_init(void);

#endif // MOSS_KERN_BOOTLOADER_H
