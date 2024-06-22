#include "bootloader.h"
#include <io/console.h>

static volatile struct limine_hhdm_request hhdm_request = { LIMINE_HHDM_REQUEST, 0, nullptr };
static volatile struct limine_kernel_address_request kernel_address_request = { LIMINE_KERNEL_ADDRESS_REQUEST, 0, nullptr };
static volatile struct limine_framebuffer_request framebuffer_request = { LIMINE_FRAMEBUFFER_REQUEST, 0, nullptr };
static volatile struct limine_memmap_request memmap_request = { LIMINE_MEMMAP_REQUEST, 0, nullptr };

void bootloader_init(void)
{
   bootloader.hhdm = hhdm_request.response;
   bootloader.kernel_address = kernel_address_request.response;
   bootloader.memmap = memmap_request.response;
   bootloader.fb = framebuffer_request.response;

   for (u64 i = 0; i < bootloader.memmap->entry_count; i++) {
      if (bootloader.memmap->entries[i]->type != LIMINE_MEMMAP_RESERVED)
         bootloader.totalUsableMemory += bootloader.memmap->entries[i]->length;
   }
}

