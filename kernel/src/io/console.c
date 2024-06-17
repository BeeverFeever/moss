#include "console.h"

#include <bootloader.h>

static struct flanterm_context* ftCtx;

void console_init()
{
   struct limine_framebuffer* framebuffer = bootloader_framebuffer->framebuffers[0];
   (void)ftCtx;
   (void)framebuffer;
}

void console_write(s8 str)
{
   (void)str;
}
