#ifndef MOSS_KERN_PORT_H
#define MOSS_KERN_PORT_H

u8 inb(u16 port);
void outb(u16 port, Byte data);

#endif // MOSS_KERN_PORT_H
