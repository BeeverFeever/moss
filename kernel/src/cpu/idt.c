#include "idt.h"
#include <utils/memory.h>

extern void* isr_stub_table[];

#define IDT_ENTRIES 256

__attribute__((aligned(0x10)))
static IDTEntry idt[IDT_ENTRIES] = {0};
static IDTR idtr;

static void idt_set_gate(u8 vector, u64 isr, u16 selector, u8 flags) {
    idt[vector].offsetLow = isr & 0xffff;
    idt[vector].selector = selector;
    idt[vector].ist = 0;
    idt[vector].gateType = flags;
    idt[vector].offsetMid = (isr >> 16) & 0xffff;
    idt[vector].offsetHigh = (isr >> 32) & 0xffffffff;
    idt[vector].reserved = 0;
}

void idt_init(void)
{
    idtr.base = idt;
    idtr.limit = sizeof(IDTEntry) * 256 - 1;

    memset(&idt, 0, sizeof(IDTEntry) * IDT_ENTRIES);

    // add ISR's here
    for (u16 vector = 0; vector < 255; vector++) {
        idt_set_gate(vector, (u64)isr_stub_table[vector], 0x28, 0x8e);
    }

    asm("lidt %0" :: "m"(idtr));
    asm("sti");
}
