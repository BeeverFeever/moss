#include <limine/limine.h>

#include <bootloader.h>
#include <cpu/gdt.h>
#include <cpu/idt.h>
#include <cpu/port.h>
#include <cpu/system.h>
#include <io/console.h>
#include <io/framebuffer.h>
#include <utils/ansi.h>
#include <utils/memory.h>
#include <utils/printf.h>

const char* memmap_type_lookup_table[8] = {
   [LIMINE_MEMMAP_USABLE] = "Usable",
   [LIMINE_MEMMAP_RESERVED] = "Reserved",
   [LIMINE_MEMMAP_ACPI_RECLAIMABLE] = "ACPI reclaimable",
   [LIMINE_MEMMAP_ACPI_NVS] = "ACPI nvs",
   [LIMINE_MEMMAP_BAD_MEMORY] = "Bad Memory",
   [LIMINE_MEMMAP_BOOTLOADER_RECLAIMABLE] = "Bootloader Reclaimable",
   [LIMINE_MEMMAP_KERNEL_AND_MODULES] = "Kernel and Modules",
   [LIMINE_MEMMAP_FRAMEBUFFER] = "Framebuffer",
};

#define u32BitMask(size,shift) (size == 0 ? 0x00000000 : ((0xffffffff >> (32 - size)) << shift))

static volatile LIMINE_BASE_REVISION(2)
__attribute__((aligned (8)))
void kernel_main(void) {
   if (LIMINE_BASE_REVISION_SUPPORTED == false) {
      panic(null);
   }

   bootloader_init();
   fb_init();
   console_init();
   printf_(colour(FG_GREEN) "Kernel start\n");

   gdt_init();
   printf_(colour(FG_YELLOW) "\tGDT" reset(R_ALL) " initialised\n");
   idt_init();
   printf_(colour(FG_YELLOW) "\tIDT" reset(R_ALL) " initialised\n");

   // memset(fb->address, 0xffffffff, fb->height * fb->pitch);
   // printf_("Total memory: %lu\n", bootloader.totalUsableMemory); 
   // printf_(colour(FG_RED)"%-13s %-12s %s\n"reset(R_ALL), "Base", "Length", "Type");
   // for (Lusize i = 0; i < bootloader.memmap->entry_count; i++) {
   //    printf_("%0#13x %0#12x %s\n", (unsigned)bootloader.memmap->entries[i]->base, (unsigned)bootloader.memmap->entries[i]->length, memmap_type_lookup_table[bootloader.memmap->entries[i]->type]);
   // }

   // fb_draw_rect(10, 210, 30, 430, 255, 0, 0);
   // fb_draw_rect(10, 210, 230, 630, 0, 255, 0);
   fb_draw_rect(10, 210, 430, 830, 0, 0, 255);
   // fb_draw_rect(0, 100, 10, 100, 100, 100, 0);
   // fb_draw_rect(0, fb.height, 0, fb.width, 200, 223, 0);

   // for (int i = 10; i < 200; i++) {
   //    fb_put_pixel(10, i, 255, 255, 255);
   // }

   // Just hang
   panic("kernel has finished.");
   // panic(null);
}
