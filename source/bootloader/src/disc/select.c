#include <disc/select.h>

#include <sys/asm/out.h>
#include <sys/asm/in.h>

bool disc_select(ata_pio_io_port_t * io_port, uint8_t drive_id) {
    outb_ptr(&io_port->drive_head, drive_id);
    outb_ptr(&io_port->lba_low, 0);
    outb_ptr(&io_port->lba_mid, 0);
    outb_ptr(&io_port->lba_high, 0);
    outb_ptr(&io_port->command, ATA_PIO_COMMAND_IDENTIFY);

    union { uint8_t uint8; ata_pio_status_t value; } status = { .uint8 = inb(0x1F7), };
    for (int i = 0; i < 256; i++) {
        while ((status.value.busy || !status.value.ready) && !status.value.error) status.uint8 = inb(0x1F7);
        if (status.value.error) {
            return false;
        }

        inw(0x1F0);
    }

    return true;
}