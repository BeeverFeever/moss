#include "bootloader.h"

__attribute__((used, section(".requests_start_marker")))
static volatile LIMINE_REQUESTS_START_MARKER;

static volatile struct limine_hhdm_request hhdm_request = { LIMINE_HHDM_REQUEST, 0, nullptr };
static volatile struct limine_kernel_address_request kernel_address_request = { LIMINE_KERNEL_ADDRESS_REQUEST, 0, nullptr };
static volatile struct limine_framebuffer_request framebuffer_request = { LIMINE_FRAMEBUFFER_REQUEST, 0, nullptr };
static volatile struct limine_memmap_request memmap_request = { LIMINE_MEMMAP_REQUEST, 0, nullptr };

__attribute__((used, section(".requests_end_marker")))
static volatile LIMINE_REQUESTS_END_MARKER;

void bootloader_init(void)
{
   bootloader.hhdm = hhdm_request.response;
   bootloader.kernel_address = kernel_address_request.response;
   bootloader.memmap = memmap_request.response;
   bootloader.framebuffer = framebuffer_request.response;
}

