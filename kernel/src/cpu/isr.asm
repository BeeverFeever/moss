bits 64

extern interrupt_handler

common_interrupt_handler:
   push rax
   push rcx
   push rdx
   push rbx
   push rsp
   push rbp
   push rsi
   push rdi
   push r8
   push r9
   push r10
   push r11
   push r12
   push r13
   push r14
   push r15

   call interrupt_handler

   pop rax
   pop rcx
   pop rdx
   pop rbx
   pop rsp
   pop rbp
   pop rsi
   pop rdi
   pop r8
   pop r9
   pop r10
   pop r11
   pop r12
   pop r13
   pop r14
   pop r15

   iretq

%macro isr_err_stub 1
isr%+%1:
   push 0
   push %1
   jmp common_interrupt_handler
%endmacro

%macro isr_no_err_stub 1
isr%+%1:
   push %1
   jmp common_interrupt_handler
%endmacro

isr_no_err_stub 0
isr_no_err_stub 1
isr_no_err_stub 2
isr_no_err_stub 3
isr_no_err_stub 4
isr_no_err_stub 5
isr_no_err_stub 6
isr_no_err_stub 7
isr_err_stub    8
isr_no_err_stub 9
isr_err_stub    10
isr_err_stub    11
isr_err_stub    12
isr_err_stub    13
isr_err_stub    14
isr_no_err_stub 15
isr_no_err_stub 16
isr_err_stub    17
isr_no_err_stub 18
isr_no_err_stub 19
isr_no_err_stub 20
isr_no_err_stub 21
isr_no_err_stub 22
isr_no_err_stub 23
isr_no_err_stub 24
isr_no_err_stub 25
isr_no_err_stub 26
isr_no_err_stub 27
isr_no_err_stub 28
isr_no_err_stub 29
isr_err_stub    30
isr_no_err_stub 31


section .data

global isr_stub_table
isr_stub_table:
%assign i 0
%rep 32
   dq isr%+i
   %assign i i+1
%endrep
