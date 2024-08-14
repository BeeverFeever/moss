#include "console.h"

#include <bootloader.h>
#include <utils/string.h>
#include <io/framebuffer.h>
// #include <io/flanterm/flanterm.h>
#include <io/flanterm/backends/fb.h>

static struct flanterm_context* ftCtx;

void console_init()
{
   ftCtx = flanterm_fb_simple_init(fb.ptr, fb.width, fb.height, fb.pitch);
   ftCtx->tab_size = 3;
}

void putchar_(char c) { flanterm_write(ftCtx, &c, 1); }
