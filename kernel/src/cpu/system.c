#include "system.h"

#include <utils/printf.h>
#include <utils/ansi.h>

void panic(char* msg) {
   if (msg != null) {
      printf_(colour(BG_RED)"[panic :)] %s\n"reset(R_ALL), msg);
   }
   asm("cli");
   for (;;) {
      asm("hlt");
   }
}

