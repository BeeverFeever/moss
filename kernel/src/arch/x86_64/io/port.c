#include "port.h"

Byte port_in_byte(U16 port) {
    Byte data;
    asm("inb %1, %0" : "=a"(data) : "Nd"(port));
    return data;
}

void port_out_byte(U16 port, Byte data) {
    asm("outb %0, %1" :: "a"(data), "Nd"(port));
}
