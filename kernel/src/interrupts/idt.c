#include <mossmemory.h>

#include "idt.h"

void handle_interrupt(void);

__attribute__((aligned(0x10)))
static IDTEntry idt[256];
static IDTR idtr;

static void idt_set_gate(U8 vector, void* isr, U8 flags) {
    idt[vector].offsetLow = (U64)isr & 0xffff;
    idt[vector].selector = 0x28;
    idt[vector].ist = 0;
    idt[vector].gateType = flags;
    idt[vector].offsetMid = ((U64)isr >> 16) & 0xffff;
    idt[vector].offsetHigh = ((U64)isr >> 32) & 0xffffffff;
    idt[vector].reserved = 0;
}

void idt_init(void)
{
    idtr.base = idt;
    idtr.limit = sizeof(IDTEntry) * 256 - 1;

    memset(&idt, 0, sizeof(IDTEntry) * 256);

    // add ISR's here
    /* for (U8 vector = 0; vector <= 255; vector++) { */
    /*     idt_set_gate(vector, handle_interrupt, 0x8e); */
    /* } */

    asm("lidt %0" :: "m"(idtr));
}

__attribute__((noreturn))
void handle_interrupt(void) {
    asm("cli; hlt"); // Completely hangs the computer
}
