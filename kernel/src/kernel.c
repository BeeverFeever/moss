#include <mossint.h>
#include <mossansi.h>
#include <mossstring.h>

#include <limine/limine.h>

#include <flanterm/flanterm.h>
#include <flanterm/backends/fb.h>

#include "interrupts/gdt.h"
#include "interrupts/idt.h"

LIMINE_BASE_REVISION(1)

struct limine_framebuffer_request framebuffer_request = {
    .id = LIMINE_FRAMEBUFFER_REQUEST,
    .revision = 0
};

// Halt and catch fire function.
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


    // Ensure we got a framebuffer.
    if (framebuffer_request.response == NULL
     || framebuffer_request.response->framebuffer_count < 1) {
        hcf();
    }

    struct limine_framebuffer* framebuffer = framebuffer_request.response->framebuffers[0];

    struct flanterm_context* ft_ctx = flanterm_fb_simple_init(framebuffer->address, framebuffer->width, framebuffer->height, framebuffer->pitch);
    ft_ctx->tab_size = 4;

    print(ft_ctx, "Welcome to " bold(GREEN) "MOSS\n" reset(R_ALL));

    asm("cli");
    gdt_init();
    print(ft_ctx, colour(YELLOW) "\tGDT" reset(R_ALL) " initialised\n");
    idt_init();
    print(ft_ctx, colour(YELLOW) "\tIDT" reset(R_ALL) " initialised\n");

    /* const char msg[] = "Hello world\n"; */

    /* flanterm_write(ft_ctx, msg, sizeof(msg)); */

    // Note: we assume the framebuffer model is RGB with 32-bit pixels.
    /* for (Size i = 0; i < 100; i++) { */
    /*     volatile uint32_t *fb_ptr = framebuffer->address; */
    /*     fb_ptr[i * (framebuffer->pitch / 4) + i] = 0xffffff; */
    /* } */

    // We're done, just hang...
    hcf();
}
