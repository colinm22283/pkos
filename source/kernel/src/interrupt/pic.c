#include <sys/asm/in.h>
#include <sys/asm/out.h>
#include <sys/asm/io_wait.h>
#include <sys/ports.h>

#include <interrupt/pic.h>

void pic_remap(uint8_t master_offset, uint8_t slave_offset) {
    uint8_t master_mask, slave_mask;

    master_mask = inb(PORT_PIC1_DATA);
    slave_mask  = inb(PORT_PIC2_DATA);

    outb(PORT_PIC1_COMMAND, ICW1_INIT | ICW1_ICW4);
    io_wait();
    outb(PORT_PIC2_COMMAND, ICW1_INIT | ICW1_ICW4);
    io_wait();
    outb(PORT_PIC1_DATA, master_offset);
    io_wait();
    outb(PORT_PIC2_DATA, slave_offset);
    io_wait();
    outb(PORT_PIC1_DATA, 4);
    io_wait();
    outb(PORT_PIC2_DATA, 2);
    io_wait();

    outb(PORT_PIC1_DATA, ICW4_8086);
    io_wait();
    outb(PORT_PIC2_DATA, ICW4_8086);
    io_wait();

    outb(PORT_PIC1_DATA, master_mask);
    outb(PORT_PIC2_DATA, slave_mask);
}