#include "console.h"

#include <bootloader.h>
#include <io/flanterm/flanterm.h>
#include <io/flanterm/backends/fb.h>

static struct flanterm_context* ftCtx;

void console_init()
{
   struct limine_framebuffer* framebuffer = bootloader.framebuffer->framebuffers[0];
   ftCtx = flanterm_fb_simple_init(framebuffer->address, framebuffer->width, framebuffer->height, framebuffer->pitch);
   ftCtx->tab_size = 3;
}

void console_write(s8 str)
{
   flanterm_write(ftCtx, str.str, str.length);
}
