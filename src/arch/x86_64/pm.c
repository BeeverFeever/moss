#include <mosslibc/defines.h>

#include "logging.h"
#include "pm.h"

static struct GDT gdt __attribute__((aligned(8)));
static struct TablePtr gdtr = (struct TablePtr){ .base = (u64)&gdt, .limit = sizeof(gdt) - 1 };
static struct IDTEntry idt[256] __attribute__((aligned(0x10)));
static struct TablePtr idtr = (struct TablePtr){ .base = (u64)idt, .limit = sizeof(struct IDTEntry) * 256 - 1 };

u64* get_idt_targets(void);

static void init_idt(void) 
{
    u64* handlers = get_idt_targets();
    for (u8 i = 0; i <= 255; i++) {
        u64 handler = handlers[i];
        idt[i] = (struct IDTEntry) {
            .offsetLow = (u32)handler,
            .selector = 0x28,
            .ist = 0,
            .flags = 0x8E,
            .offsetMid = handler >> 16,
            .offsetHigh = handler >> 32,
            .reserved = 0
        };
    }
 
    asm("lidt %0" :: "m"(idtr));
}

void handle_interrupt(void) 
{
    fatal("Unexpected interrupt!");
    asm("cli; hlt;");
}

static void init_gdt(void) 
{
    // NOTE: array size needs to be chanegd accordingly if more entries are added to
    // gdt
    gdt.entries[0] = 0x0000000000000000; // first one is empty
    gdt.entries[1] = 0x00af9b00000fffff; // 64-bit code
    gdt.entries[2] = 0x00af9300000fffff; // 64-bit data
    gdt.entries[3] = 0x00affb00000fffff; // usermode 64-bit code
    gdt.entries[4] = 0x00aff300000fffff; // usermode 64-bit data

    asm("lgdt %0;" :: "m"(gdtr));
    success("GDT loaded");
}

void enter_protected_mode(void) 
{
    asm ("cli");
    init_gdt();
    init_idt();
    asm ("sti");
    success("In protected mode");
}
