#include <limine/limine.h>

#include <mossansi.h>

#include <io/console.h>
#include <bootloader/limine.h>
#include <arch/x86_64/gdt.h>
#include <arch/x86_64/interrupts/idt.h>

LIMINE_BASE_REVISION(2)

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
   console_init();

   asm("cli");
   gdt_init();
   console_write(s8(colour(FG_YELLOW) "\tGDT" reset(R_ALL) " initialised\n"));
   idt_init();
   console_write(s8(colour(FG_YELLOW) "\tIDT" reset(R_ALL) " initialised\n"));

   // Note: we assume the framebuffer model is RGB with 32-bit pixels.
   for (u32 i = 0; i < 100; i++) {
       volatile u32* fb_ptr = bootloader_framebuffer->framebuffers[0]->address;
       fb_ptr[i * (bootloader_framebuffer->framebuffers[0]->pitch / 4) + i] = 0xffffffff;
   }

   // We're done, just hang...
   hcf();
}
