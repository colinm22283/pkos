#include <disc/read.h>

#include <sys/asm/out.h>
#include <sys/asm/in.h>

#include <console/print.h>

uint32_t disc_read28(ata_pio_io_port_t * io_port, uint8_t drive_select, uint32_t lba, uint8_t sector_count, uint16_t * dest) {
    // TODO: impliment io_port variable
    if (lba > 0xFFFFFF) return 1;

    outb_ptr(&io_port->drive_head, drive_select | ((lba >> 24) & 0xF));
    outb_ptr(&io_port->features, 0);

    outb_ptr(&io_port->sector_count, sector_count);

    outb_ptr(&io_port->lba_low, lba);
    outb_ptr(&io_port->lba_mid, lba >> 8);
    outb_ptr(&io_port->lba_high, lba >> 16);

    outb_ptr(&io_port->command, ATA_PIO_COMMAND_READ);

    union { uint8_t uint8; ata_pio_status_t value; } status;

    inb_ptr(&io_port->status);
    inb_ptr(&io_port->status);
    inb_ptr(&io_port->status);
    status.uint8 = inb_ptr(&io_port->status);

    for (int i = 0; i < sector_count; i++) {
        while ((status.value.busy || !status.value.ready) && !status.value.error) status.uint8 = inb_ptr(&io_port->status);
        if (status.value.error) {
            return 2;
        }

        for (int j = 0; j < 256; j++) {
            *dest = inw_ptr(&io_port->data);

            dest++;

            while ((status.value.busy || !status.value.ready) && !status.value.error) status.uint8 = inb_ptr(&io_port->status);
        }

        inb_ptr(&io_port->status);
        inb_ptr(&io_port->status);
        inb_ptr(&io_port->status);
        status.uint8 = inb_ptr(&io_port->status);
    }

    if (status.value.error) {
        return 3;
    }

    return 0;
}

uint32_t disc_read48(ata_pio_io_port_t * io_port, uint8_t drive_select, uint64_t lba, uint16_t sector_count, uint16_t * dest) {
    if (lba > 0xFFFFFFFFFFFF) return 1;

    outb_ptr(&io_port->drive_head, drive_select);

    outb_ptr(&io_port->sector_count, sector_count >> 8);
    outb_ptr(&io_port->lba_low, lba >> 24);
    outb_ptr(&io_port->lba_mid, lba >> 32);
    outb_ptr(&io_port->lba_high, lba >> 40);
    outb_ptr(&io_port->sector_count, sector_count & 0xFF);
    outb_ptr(&io_port->lba_low, lba >> 0);
    outb_ptr(&io_port->lba_mid, lba >> 8);
    outb_ptr(&io_port->lba_high, lba >> 16);
    outb_ptr(&io_port->command, 0x24);

    union { uint8_t uint8; ata_pio_status_t value; } status = { .uint8 = inb_ptr(&io_port->status), };
    for (int i = 0; i < sector_count; i++) {
        while ((status.value.busy || !status.value.ready) && !status.value.error) status.uint8 = inb(0x1F7);
        if (status.value.error) {
            return 2;
        }

        for (int j = 0; j < 256; j++) {
            *dest = inw(0x1F0);

            dest++;

            while ((status.value.busy || !status.value.ready) && !status.value.error) status.uint8 = inb(0x1F7);
        }

        status.uint8 = inb_ptr(&io_port->status);
    }

    return 0;
}