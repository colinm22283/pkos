#pragma once

#define PORT_PIC1         (0x20)
#define PORT_PIC2         (0xA0)
#define PORT_PIC1_COMMAND (PORT_PIC1)
#define PORT_PIC1_DATA    (PORT_PIC1 + 1)
#define PORT_PIC2_COMMAND (PORT_PIC2)
#define PORT_PIC2_DATA    (PORT_PIC2 + 1)

#define PORT_KB_IN  (0x60)
#define PORT_KB_OUT (0x61)

#define ATA_PIO_PRIMARY           ((void *) 0x1F0)
#define ATA_PIO_SECONDARY         ((void *) 0x170)
#define ATA_PIO_PRIMARY_CONTROL   ((void *) 0x3F6)
#define ATA_PIO_SECONDARY_CONTROL ((void *) 0x376)