#include "idt.h"
#include <utils/memory.h>

constexpr u32 IDT_ENTRIES = 256;

extern void* isr_stub_table[];
static bool vectors[IDT_ENTRIES];

__attribute__((aligned(0x10)))
static IDTEntry idt[IDT_ENTRIES] = {0};
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
    idtr.base = (uintptr)&idt[0];
    idtr.limit = (u16)sizeof(IDTEntry) * IDT_ENTRIES - 1;

    memset(&idt, 0, sizeof(IDTEntry) * IDT_ENTRIES);

    // add ISR's here
    for (u16 vector = 0; vector < 255; vector++) {
        idt_set_gate(vector, isr_stub_table[vector], 0x8e);
        vectors[vector] = true;
    }

    asm("lidt %0" :: "m"(idtr));
    asm("sti");
}
