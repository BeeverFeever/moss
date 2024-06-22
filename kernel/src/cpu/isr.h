#ifndef MOSS_KERN_ISR_H
#define MOSS_KERN_ISR_H

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

extern void interrupt_handler(void);

#endif // MOSS_KERN_ISR_H
