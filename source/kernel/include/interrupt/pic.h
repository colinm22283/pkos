#pragma once

#include <stdint.h>

#include <sys/asm/out.h>
#include <sys/asm/in.h>
#include <sys/ports.h>

#define ICW1_ICW4       (0x01)
#define ICW1_SINGLE     (0x02)
#define ICW1_INTERVAL4  (0x04)
#define ICW1_LEVEL      (0x08)
#define ICW1_INIT       (0x10)

#define ICW4_8086       (0x01)
#define ICW4_AUTO       (0x02)
#define ICW4_BUF_SLAVE  (0x08)
#define ICW4_BUF_MASTER (0x0C)
#define ICW4_SFNM       (0x10)

void pic_remap(uint8_t master_offset, uint8_t slave_offset);

static inline void pic_set_mask(unsigned char irq_line) {
    uint16_t port;
    uint8_t value;

    if(irq_line < 8) {
        port = PORT_PIC1_DATA;
    } else {
        port = PORT_PIC2_DATA;
        irq_line -= 8;
    }
    value = inb(port) | (1 << irq_line);
    outb(port, value);
}

static inline void pic_mask_all() {
    outb(PORT_PIC1_DATA, 0xFF);
    outb(PORT_PIC2_DATA, 0xFF);
}

static inline void pic_clear_mask(unsigned char irq_line) {
    uint16_t port;
    uint8_t value;

    if(irq_line < 8) {
        port = PORT_PIC1_DATA;
    } else {
        port = PORT_PIC2_DATA;
        irq_line -= 8;
    }
    value = inb(port) & ~(1 << irq_line);
    outb(port, value);
}