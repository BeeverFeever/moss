#pragma once

typedef struct {
   U16 offsetLow;   // offset bits 0..15
   U16 selector;    // a code segment selector in GDT or LDT
   U8 ist;          // bits 0..2 holds Interrupt Stack Table offset, rest of bits zero.
   U8 gateType;        // gate type, dpl, and p fields
   U16 offsetMid;   // offset bits 16..31
   U32 offsetHigh;  // offset bits 32..63
   U32 reserved;        // reserved
} __attribute__((packed)) IDTEntry;

typedef struct {
    U16 limit;
    IDTEntry* base;
} __attribute__((packed)) IDTR;

typedef struct {
    U64 rax, rcx, rdx, rbx, rsp, rbp, rsi, rdi;
    U64 r8, r9, r10, r11, r12, r13, r14, r15;
} __attribute__((packed)) CpuState;

typedef struct {
    U64 error_code;
    U64 eip;
    U64 cs;
    U64 eflags;
} __attribute__((packed)) StackState;

void idt_init(void);
