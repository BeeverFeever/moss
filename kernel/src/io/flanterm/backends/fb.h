/* Copyright (C) 2022-2024 mintsuki and contributors.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef FLANTERM_FB_H
#define FLANTERM_FB_H 1

#ifdef __cplusplus
extern "C" {
#endif

// #include <stdint.h>
// #include <stddef.h>
// #include <stdbool.h>

#include "../flanterm.h"

#define FLANTERM_FB_FONT_GLYPHS 256

struct flanterm_fb_char {
    u32 c;
    u32 fg;
    u32 bg;
};

struct flanterm_fb_queue_item {
    Size x, y;
    struct flanterm_fb_char c;
};

struct flanterm_fb_context {
    struct flanterm_context term;

    Size font_width;
    Size font_height;
    Size glyph_width;
    Size glyph_height;

    Size font_scale_x;
    Size font_scale_y;

    Size offset_x, offset_y;

    volatile u32 *framebuffer;
    Size pitch;
    Size width;
    Size height;
    Size bpp;

#ifdef FLANTERM_FB_SUPPORT_BPP
    u8 red_mask_size, red_mask_shift;
    u8 green_mask_size, green_mask_shift;
    u8 blue_mask_size, blue_mask_shift;
#endif

    Size font_bits_size;
    u8 *font_bits;
    Size font_bool_size;
    Bool *font_bool;

    u32 ansi_colours[8];
    u32 ansi_bright_colours[8];
    u32 default_fg, default_bg;
    u32 default_fg_bright, default_bg_bright;

#ifndef FLANTERM_FB_DISABLE_CANVAS
    Size canvas_size;
    u32 *canvas;
#endif

    Size grid_size;
    Size queue_size;
    Size map_size;

    struct flanterm_fb_char *grid;

    struct flanterm_fb_queue_item *queue;
    Size queue_i;

    struct flanterm_fb_queue_item **map;

    u32 text_fg;
    u32 text_bg;
    Size cursor_x;
    Size cursor_y;

    u32 saved_state_text_fg;
    u32 saved_state_text_bg;
    Size saved_state_cursor_x;
    Size saved_state_cursor_y;

    Size old_cursor_x;
    Size old_cursor_y;
};

struct flanterm_context *flanterm_fb_init(
    void *(*_malloc)(Size),
    void (*_free)(void *, Size),
    u32 *framebuffer, Size width, Size height, Size pitch,
#ifdef FLANTERM_FB_SUPPORT_BPP
    u8 red_mask_size, u8 red_mask_shift,
    u8 green_mask_size, u8 green_mask_shift,
    u8 blue_mask_size, u8 blue_mask_shift,
#endif
#ifndef FLANTERM_FB_DISABLE_CANVAS
    u32 *canvas,
#endif
    u32 *ansi_colours, u32 *ansi_bright_colours,
    u32 *default_bg, u32 *default_fg,
    u32 *default_bg_bright, u32 *default_fg_bright,
    void *font, Size font_width, Size font_height, Size font_spacing,
    Size font_scale_x, Size font_scale_y,
    Size margin
);

#ifndef FLANTERM_FB_DISABLE_BUMP_ALLOC
static inline struct flanterm_context *flanterm_fb_simple_init(
    u32 *framebuffer, Size width, Size height, Size pitch
#ifdef FLANTERM_FB_SUPPORT_BPP
    ,
    u8 red_mask_size, u8 red_mask_shift,
    u8 green_mask_size, u8 green_mask_shift,
    u8 blue_mask_size, u8 blue_mask_shift
#endif
) {
    Size font_scale_x = 1;
    Size font_scale_y = 1;
    if (width >= (1920 + 1920 / 3) && height >= (1080 + 1080 / 3)) {
        font_scale_x = 2;
        font_scale_y = 2;
    }
    if (width >= (3840 + 3840 / 3) && height >= (2160 + 2160 / 3)) {
        font_scale_x = 4;
        font_scale_y = 4;
    }

    return flanterm_fb_init(
        null,
        null,
        framebuffer, width, height, pitch,
#ifdef FLANTERM_FB_SUPPORT_BPP
        red_mask_size, red_mask_shift,
        green_mask_size, green_mask_shift,
        blue_mask_size, blue_mask_shift,
#endif
#ifndef FLANTERM_FB_DISABLE_CANVAS
        null,
#endif
        null, null,
        null, null,
        null, null,
        null, 0, 0, 1,
        font_scale_x, font_scale_y,
        0
    );
}
#endif

#ifdef __cplusplus
}
#endif

#endif
