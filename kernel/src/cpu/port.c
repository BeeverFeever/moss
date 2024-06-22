#include "port.h"

Byte inb(u16 port) {
    Byte data;
    asm("inb %1, %0" : "=a"(data) : "Nd"(port));
    return data;
}

void outb(u16 port, Byte data) {
    asm("outb %0, %1" :: "a"(data), "Nd"(port));
}
