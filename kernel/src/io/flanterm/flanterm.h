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

#ifndef FLANTERM_H
#define FLANTERM_H 1

#ifdef __cplusplus
extern "C" {
#endif

// #include <mossdefines.h>
// #include <mossint.h>

#define FLANTERM_MAX_ESC_VALUES 16

#define FLANTERM_CB_DEC 10
#define FLANTERM_CB_BELL 20
#define FLANTERM_CB_PRIVATE_ID 30
#define FLANTERM_CB_STATUS_REPORT 40
#define FLANTERM_CB_POS_REPORT 50
#define FLANTERM_CB_KBD_LEDS 60
#define FLANTERM_CB_MODE 70
#define FLANTERM_CB_LINUX 80

#define FLANTERM_OOB_OUTPUT_OCRNL (1 << 0)
#define FLANTERM_OOB_OUTPUT_OFDEL (1 << 1)
#define FLANTERM_OOB_OUTPUT_OFILL (1 << 2)
#define FLANTERM_OOB_OUTPUT_OLCUC (1 << 3)
#define FLANTERM_OOB_OUTPUT_ONLCR (1 << 4)
#define FLANTERM_OOB_OUTPUT_ONLRET (1 << 5)
#define FLANTERM_OOB_OUTPUT_ONOCR (1 << 6)
#define FLANTERM_OOB_OUTPUT_OPOST (1 << 7)

struct flanterm_context {
    /* internal use */

    Size tab_size;
    Bool autoflush;
    Bool cursor_enabled;
    Bool scroll_enabled;
    Bool control_sequence;
    Bool csi;
    Bool escape;
    Bool osc;
    Bool osc_escape;
    Bool rrr;
    Bool discard_next;
    Bool bold;
    Bool bg_bold;
    Bool reverse_video;
    Bool dec_private;
    Bool insert_mode;
    u64 code_point;
    Size unicode_remaining;
    u8 g_select;
    u8 charsets[2];
    Size current_charset;
    Size escape_offset;
    Size esc_values_i;
    Size saved_cursor_x;
    Size saved_cursor_y;
    Size current_primary;
    Size current_bg;
    Size scroll_top_margin;
    Size scroll_bottom_margin;
    u32 esc_values[FLANTERM_MAX_ESC_VALUES];
    u64 oob_output;
    Bool saved_state_bold;
    Bool saved_state_bg_bold;
    Bool saved_state_reverse_video;
    Size saved_state_current_charset;
    Size saved_state_current_primary;
    Size saved_state_current_bg;

    /* to be set by backend */

    Size rows, cols;

    void (*raw_putchar)(struct flanterm_context *, u8 c);
    void (*clear)(struct flanterm_context *, Bool move);
    void (*set_cursor_pos)(struct flanterm_context *, Size x, Size y);
    void (*get_cursor_pos)(struct flanterm_context *, Size *x, Size *y);
    void (*set_text_fg)(struct flanterm_context *, Size fg);
    void (*set_text_bg)(struct flanterm_context *, Size bg);
    void (*set_text_fg_bright)(struct flanterm_context *, Size fg);
    void (*set_text_bg_bright)(struct flanterm_context *, Size bg);
    void (*set_text_fg_rgb)(struct flanterm_context *, u32 fg);
    void (*set_text_bg_rgb)(struct flanterm_context *, u32 bg);
    void (*set_text_fg_default)(struct flanterm_context *);
    void (*set_text_bg_default)(struct flanterm_context *);
    void (*set_text_fg_default_bright)(struct flanterm_context *);
    void (*set_text_bg_default_bright)(struct flanterm_context *);
    void (*move_character)(struct flanterm_context *, Size new_x, Size new_y, Size old_x, Size old_y);
    void (*scroll)(struct flanterm_context *);
    void (*revscroll)(struct flanterm_context *);
    void (*swap_palette)(struct flanterm_context *);
    void (*save_state)(struct flanterm_context *);
    void (*restore_state)(struct flanterm_context *);
    void (*double_buffer_flush)(struct flanterm_context *);
    void (*full_refresh)(struct flanterm_context *);
    void (*deinit)(struct flanterm_context *, void (*)(void *, Size));

    /* to be set by client */

    void (*callback)(struct flanterm_context *, u64, u64, u64, u64);
};

void flanterm_context_reinit(struct flanterm_context *ctx);
void flanterm_write(struct flanterm_context *ctx, const char *buf, Size count);

#ifdef __cplusplus
}
#endif

#endif
