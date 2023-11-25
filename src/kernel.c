#include <mosslibc/stddef.h>
#include <mosslibc/defines.h>
#include <arch/x86_64/interrupts/protected-mode.h>

#include <flanterm/flanterm.h>
#include <flanterm/backends/fb.h>
#include "bootloader/limine.h"
#define OLIVEC_IMPLEMENTATION
#include "olive.h"

// The Limine requests can be placed anywhere, but it is important that
// the compiler does not optimise them away, so, usually, they should
// be made volatile or equivalent.

static volatile struct limine_framebuffer_request framebuffer_request = {
    .id = LIMINE_FRAMEBUFFER_REQUEST,
    .revision = 0
};

// Halt and catch fire function.
static void hang(void) {
    asm ("cli");
    for (;;) {
        asm ("hlt");
    }
}

// The following will be our kernel's entry point.
// NOTE: Please don't change name of this function.
void kernel_start(void) {
    asm("cli");
    // gdt_init();
    idt_init();
    asm("sti");


    // Ensure we got a framebuffer.
    if (framebuffer_request.response == NULL
     || framebuffer_request.response->framebuffer_count < 1) {
        hang();
    }


    // Fetch the first framebuffer.
    struct limine_framebuffer *framebuffer = framebuffer_request.response->framebuffers[0];
    u32* volatile fb_ptr = framebuffer->address;
    Olivec_Canvas canvas = olivec_canvas(fb_ptr, framebuffer->width, framebuffer->height, framebuffer->pitch);

    struct flanterm_context *ft_ctx = flanterm_fb_simple_init(
        framebuffer->address, framebuffer->width, framebuffer->height, framebuffer->pitch
    );

    const char msg[] = "\033[1;35mKernel\033[0m Hello world\n";

    flanterm_write(ft_ctx, msg, sizeof(msg));

    olivec_fill(canvas, 0xff222222);
    olivec_circle(canvas, 50, 50, 40, 0xffffffff);

    hang();
}
