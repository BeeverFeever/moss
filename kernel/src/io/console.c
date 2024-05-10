#include "console.h"

#include <mossstring.h>

#include <bootloader.h>

static struct flanterm_context* fb = framebuffer_request.response->framebuffer[0];

void console_init()
{

}

void console_write(String str)
{
    if (term_ctx) flanterm_write(term_ctx, str, strlen(str));
}
