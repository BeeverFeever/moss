#include <limine/limine.h>

#include <utils/ansi.h>
#include <bootloader.h>
#include <io/console.h>
#include <cpu/gdt.h>
#include <cpu/idt.h>

LIMINE_BASE_REVISION(2)

extern u64 kernel_rodata_start;
extern u64 kernel_rodata_end;

static void hcf(void) {
   asm("cli");
   for (;;) {
      asm("hlt");
   }
}

void kernel_main(void) {
   if (LIMINE_BASE_REVISION_SUPPORTED == false) {
      hcf();
   }

   bootloader_init();

   // memset(&kernel_rodata_start, 0, kernel_rodata_end);

   // bootloader_init();
   console_init();

   asm("cli");
   gdt_init();
   // console_write(s8(colour(FG_YELLOW) "\tGDT" reset(R_ALL) " initialised\n"));
   idt_init();
   // console_write(s8(colour(FG_YELLOW) "\tIDT" reset(R_ALL) " initialised\n"));

   // Note: we assume the framebuffer model is RGB with 32-bit pixels.
   struct limine_framebuffer* fb = bootloader_framebuffer->framebuffers[0];
   volatile u32* fb_ptr = fb->address;
   // memset(fb_ptr, 0, fb->height * fb->pitch);
   for (u32 i = 0; i < 100; i++) {
      fb_ptr[i * (bootloader_framebuffer->framebuffers[0]->pitch / 4) + i] = 0xffffffff;
   }
   // console_write(s8("hi there"));

   // for (u64 y = 0; y < fb->height; y++) {
   //    for (u64 x = 0; x < fb->width; x++) {
   //       fb_ptr[y * (fb->pitch / 4) + x] = 0xffffffff;
   //    }
   // }

   // We're done, just hang...
   hcf();
}
