#include "isr.h"

__attribute__((noreturn)) 
extern void interrupt_handler(void);

void interrupt_handler(void) {
   asm("cli; hlt;");
}
