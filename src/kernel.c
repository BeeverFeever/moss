#include <mosslibc/stddef.h>
#include <mosslibc/memory.h>
#include <mosslibc/defines.h>
#include <arch/x86_64/pm.h>

#include "bootloader/limine.h"

#define OLIVEC_IMPLEMENTATION
#include "olive.h"

// The Limine requests can be placed anywhere, but it is important that
// the compiler does not optimise them away, so, usually, they should
// be made volatile or equivalent.

// static volatile struct limine_framebuffer_request framebuffer_request = {
//     .id = LIMINE_FRAMEBUFFER_REQUEST,
//     .revision = 0
// };

// Halt and catch fire function.
static void hcf(void) {
    asm ("cli");
    for (;;) {
        asm ("hlt");
    }
}

// The following will be our kernel's entry point.
// If renaming _start() to something else, make sure to change the
// linker script accordingly.
void _start(void) {
    enter_protected_mode();        
    // Ensure we got a framebuffer.
    // if (framebuffer_request.response == NULL
    //  || framebuffer_request.response->framebuffer_count < 1) {
    //     hcf();
    // }

    // Fetch the first framebuffer.
    // struct limine_framebuffer *framebuffer = framebuffer_request.response->framebuffers[0];
    // Olivec_Canvas canvas = olivec_canvas(framebuffer->address, framebuffer->width, framebuffer->height, framebuffer->pitch);

    // olivec_fill(canvas, 0x666666ff);
    // olivec_circle(canvas, 50, 50, 40, 0xffffffff);
    // canvas.pixels = framebuffer->address;

    hcf();
}
