#include <limine/limine.h>

#define limine_module(name) extern volatile struct limine_##name##_response* bootloader_##name
#define limine_request(name) static volatile struct limine_##name##_request name##_request =

limine_module(framebuffer);

limine_request(framebuffer) { LIMINE_FRAMEBUFFER_REQUEST, 0, nullptr };

#undef limine_request
#undef limine_module

void bootloader_init(void)
{
    bootloader_framebuffer = framebuffer_request.response;
}
