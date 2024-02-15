#include <limine/limine.h>

#define limine_module(name) extern volatile struct limine##name##_response* bootloader_##name

limine_module(framebuffer);

#undef limine_module

void bootloader_init(void)
{

}
