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

void idt_init(void);
