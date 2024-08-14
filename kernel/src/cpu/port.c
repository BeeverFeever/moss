#include "port.h"

Byte inb(u16 port) {
  Byte data;
  asm volatile("inb %1, %0" : "=a"(data) : "Nd"(port) : "memory");
  return data;
}

void outb(u16 port, Byte data) {
  asm volatile("outb %0, %1" ::"a"(data), "Nd"(port) : "memory");
}

// inline bool are_interrupts_enabled()
// {
//    unsigned long flags;
//    asm volatile ( "pushf\n\t"
//          "pop %0"
//          : "=g"(flags) );
//    return flags & (1 << 9);
// }
