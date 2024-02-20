#include <disc/select.h>

#include <sys/asm/out.h>
#include <sys/asm/in.h>

bool disc_select(ata_pio_io_port_t * io_port, uint8_t drive_id) {
    outb_ptr(&io_port->drive_head, drive_id);
    outb_ptr(&io_port->lba_low, 0);
    outb_ptr(&io_port->lba_mid, 0);
    outb_ptr(&io_port->lba_high, 0);
    outb_ptr(&io_port->command, 0xEC);

    union {
        uint8_t uint8;
        ata_pio_status_t value;
    } status;

    do status.uint8 = inb_ptr(&io_port->status);
    while (status.value.busy);

    return status.uint8 != 0;
}