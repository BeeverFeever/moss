#include <mosslibc/defines.h>
#include <mosslibc/memory.h>

#include "logging.h"
#include "protected-mode.h"

__attribute__((aligned(8)))
static struct GDT gdt;
static struct TablePtr gdtr = (struct TablePtr){ .base = (u64)&gdt, .limit = sizeof(gdt) - 1 };

__attribute__((aligned(0x10)))
static struct IDTEntry idt[256];
static struct TablePtr idtr;

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
    idtr.base = &idt;
    idtr.limit = sizeof(struct IDTEntry) * 256 - 1;

    memset(&idt, 0, sizeof(struct IDTEntry) * 256);

    // add ISR's here

    asm("lidt %0" :: "m"(idtr));
}

void gdt_init(void) 
{
    // NOTE: array size in declaration needs to be chanegd accordingly if more entries are added to
    // gdt
    gdt.entries[0] = 0x0000000000000000; // first one is empty
    gdt.entries[1] = 0x00af9b00000fffff; // 64-bit code
    gdt.entries[2] = 0x00af9300000fffff; // 64-bit data
    gdt.entries[3] = 0x00affb00000fffff; // usermode 64-bit code
    gdt.entries[4] = 0x00aff300000fffff; // usermode 64-bit data

    asm("lgdt %0;" :: "m"(gdtr));
    success("GDT loaded");
}

__attribute__((noreturn))
void handle_interrupt(void) {
    asm("cli; hlt"); // Completely hangs the computer
}
