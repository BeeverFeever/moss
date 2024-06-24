#include "pic.h"

#include <cpu/port.h>

static inline void wait(void) { outb(0x80, 0); }

void picSendEOI(u8 irq)
{
	if(irq >= 8)
		outb(PIC2_COMMAND,PIC_EOI);
	
	outb(PIC1_COMMAND,PIC_EOI);
}

void picRemap(u32 offset1, u32 offset2)
{
	u8 a1, a2;
	
	a1 = inb(PIC1_DATA);                        // save masks
	a2 = inb(PIC2_DATA);
	
	outb(PIC1_COMMAND, ICW1_INIT | ICW1_ICW4);  // starts the initialization sequence (in cascade mode)
	wait();
	outb(PIC2_COMMAND, ICW1_INIT | ICW1_ICW4);
	wait();
	outb(PIC1_DATA, offset1);                 // ICW2: Master PIC vector offset
	wait();
	outb(PIC2_DATA, offset2);                 // ICW2: Slave PIC vector offset
	wait();
	outb(PIC1_DATA, 4);                       // ICW3: tell Master PIC that there is a slave PIC at IRQ2 (0000 0100)
	wait();
	outb(PIC2_DATA, 2);                       // ICW3: tell Slave PIC its cascade identity (0000 0010)
	wait();
	
	outb(PIC1_DATA, ICW4_8086);               // ICW4: have the PICs use 8086 mode (and not 8080 mode)
	wait();
	outb(PIC2_DATA, ICW4_8086);
	wait();
	
	outb(PIC1_DATA, a1);   // restore saved masks.
	outb(PIC2_DATA, a2);
}

void pic_disable(void) 
{
    outb(PIC1_DATA, 0xff);
    outb(PIC2_DATA, 0xff);
}

void picSetIRQMask(u8 IRQline) {
    u16 port;
    u8 value;

    if(IRQline < 8) {
        port = PIC1_DATA;
    } else {
        port = PIC2_DATA;
        IRQline -= 8;
    }
    value = inb(port) | (1 << IRQline);
    outb(port, value);        
}

void picClearIRQMask(u8 IRQline) {
    u16 port;
    u8 value;

    if(IRQline < 8) {
        port = PIC1_DATA;
    } else {
        port = PIC2_DATA;
        IRQline -= 8;
    }
    value = inb(port) & ~(1 << IRQline);
    outb(port, value);        
}
