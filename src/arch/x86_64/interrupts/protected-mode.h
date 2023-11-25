#pragma once

#include <mosslibc/defines.h>

struct TablePtr {
    u16 limit;
    u64 base;
} __attribute__((packed));

struct IDTEntry {
   u16 offsetLow;   // offset bits 0..15
   u16 selector;    // a code segment selector in GDT or LDT
   u8 ist;          // bits 0..2 holds Interrupt Stack Table offset, rest of bits zero.
   u8 gateType;        // gate type, dpl, and p fields
   u16 offsetMid;   // offset bits 16..31
   u32 offsetHigh;  // offset bits 32..63
   u32 reserved;        // reserved
} __attribute__((packed));

// NOTE: array size needs to be chanegd accordingly if more entries are added to
// gdt
struct GDT {
    u64 entries[10];
};

struct cpu_state {
    uint rax, rcx, rdx, rbx, rsp, rbp, rsi, rdi;
    uint r8, r9, r10, r11, r12, r13, r14, r15;
} __attribute__((packed));

struct stack_state {
    uint error_code;
    uint eip;
    uint cs;
    uint eflags;
} __attribute__((packed));

void interrupt_handler(struct cpu_state cpu, struct stack_state stack, uint interrupt);
void idt_init();
void gdt_init();
