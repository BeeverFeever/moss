#include "limine.h"

#define declare_module(name) volatile struct limine_##name##_response* bootloader_##name
#define request_module(name) static volatile struct limine_##name##_request name##_request =

declare_module(hhdm);
declare_module(kernel_address);
declare_module(framebuffer);

request_module(hhdm) { LIMINE_HHDM_REQUEST, 0, nullptr };
request_module(kernel_address) { LIMINE_KERNEL_ADDRESS_REQUEST, 0, nullptr };
request_module(framebuffer) { LIMINE_FRAMEBUFFER_REQUEST, 0, nullptr };

#undef declare_module
#undef request_module

void bootloader_init(void)
{
   bootloader_hhdm            = hhdm_request.response;
   bootloader_kernel_address  = kernel_address_request.response;
   bootloader_framebuffer     = framebuffer_request.response;
}

