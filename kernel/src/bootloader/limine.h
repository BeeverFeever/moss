#ifndef BOOTLOADER_LIMINE_H
#define BOOTLOADER_LIMINE_H

#include <limine/limine.h>

#define bootloader_module(name) extern volatile struct limine_##name##_response* bootloader_##name

bootloader_module(hhdm);
bootloader_module(kernel_address);
bootloader_module(framebuffer);

#undef bootloader_module

void bootloader_init(void);

#endif // BOOTLOADER_LIMINE_H
