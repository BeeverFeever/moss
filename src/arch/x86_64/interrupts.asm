bits 64

extern handle_interrupt

%macro idtend 1
    dq isr%1
%endmacro

%macro isrgen 1
isr%1:
    call handle_interrupt
    iretq
%endmacro

section .text

global get_idt_targets
get_idt_targets:
    lea rax, [rel idt_targets]
    ret

%assign i 0
%rep 256
isrgen i
%assign i i+1
%endrep

section .rodata

global idt_targets
idt_targets:
%assign i 0
%rep 256
    idtend i
%assign i i+1
%endrep
