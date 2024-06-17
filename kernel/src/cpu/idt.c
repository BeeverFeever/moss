#include "idt.h"
#include <utils/memory.h>

void handle_interrupt(void);

__attribute__((aligned(0x10)))
static IDTEntry idt[256];
static IDTR idtr;

static void idt_set_gate(u8 vector, void* isr, u8 flags) {
    idt[vector].offsetLow = (u64)isr & 0xffff;
    idt[vector].selector = 0x28;
    idt[vector].ist = 0;
    idt[vector].gateType = flags;
    idt[vector].offsetMid = ((u64)isr >> 16) & 0xffff;
    idt[vector].offsetHigh = ((u64)isr >> 32) & 0xffffffff;
    idt[vector].reserved = 0;
}

void idt_init(void)
{
    idtr.base = idt;
    idtr.limit = sizeof(IDTEntry) * 256 - 1;

    memset(&idt, 0, sizeof(IDTEntry) * 256);

    // add ISR's here
    /* idt_set_gate(0, handle_interrupt, 0x8); */
    /* idt_set_gate(1, handle_interrupt, 0x8); */
    /* idt_set_gate(2, handle_interrupt, 0x8); */
    /* idt_set_gate(3, handle_interrupt, 0x8); */
    /* idt_set_gate(4, handle_interrupt, 0x8); */
    /* idt_set_gate(5, handle_interrupt, 0x8); */
    /* idt_set_gate(6, handle_interrupt, 0x8); */
    /* idt_set_gate(7, handle_interrupt, 0x8); */
    /* idt_set_gate(8, handle_interrupt, 0x8); */
    /* idt_set_gate(9, handle_interrupt, 0x8); */
    /* idt_set_gate(10, handle_interrupt, 0x8); */
    /* idt_set_gate(11, handle_interrupt, 0x8); */
    /* idt_set_gate(255, handle_interrupt, 0x8); */
    for (u16 vector = 0; vector < 256; vector++) {
        idt_set_gate(vector, handle_interrupt, 0x8e);
    }

    asm("lidt %0" :: "m"(idtr));
    asm("sti");
}

__attribute__((noreturn))
void handle_interrupt(void) {
    asm("cli; hlt"); // Completely hangs the computer
}
