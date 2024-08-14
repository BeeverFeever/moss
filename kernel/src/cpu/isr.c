#include "isr.h"

#include <utils/printf.h>

__attribute__((noreturn)) 
extern void interrupt_handler(void);

void interrupt_handler(void) {
   printf_("interrupt happened\n");
   asm("cli; hlt;");
}
