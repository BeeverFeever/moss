#include "gdt.h"

__attribute__((aligned(8)))
static GDT gdt;
static GDTR gdtr = (GDTR){ .base = (u64)&gdt, .limit = sizeof(gdt) - 1 };


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
    /* success("GDT loaded"); */
}
