#pragma once

typedef struct {
   u16 offsetLow;   // offset bits 0..15
   u16 selector;    // a code segment selector in GDT or LDT
   u8 ist;          // bits 0..2 holds Interrupt Stack Table offset, rest of bits zero.
   u8 gateType;        // gate type, dpl, and p fields
   u16 offsetMid;   // offset bits 16..31
   u32 offsetHigh;  // offset bits 32..63
   u32 reserved;        // reserved
} __attribute__((packed)) IDTEntry;

typedef struct {
    u16 limit;
    IDTEntry* base;
} __attribute__((packed)) IDTR;

typedef struct {
    u64 rax, rcx, rdx, rbx, rsp, rbp, rsi, rdi;
    u64 r8, r9, r10, r11, r12, r13, r14, r15;
} __attribute__((packed)) CpuState;

typedef struct {
    u64 error_code;
    u64 eip;
    u64 cs;
    u64 eflags;
} __attribute__((packed)) StackState;

void idt_init(void);
