#include <boot/disc.h>

#include <disc/detect.h>
#include <disc/reset.h>
#include <disc/select.h>
#include <disc/read.h>

#include <sys/ports.h>

#include <console/print.h>
#include <console/print_hex.h>
#include <console/newline.h>
#include <console/print_bool.h>

#include <sys/asm/hlt.h>
#include <sys/asm/out.h>

#include <memory/memset.h>

bool boot_disc_primary_present;
bool boot_disc_secondary_present;
bool boot_disc_master_selected;

bool boot_disc_init() {
    boot_disc_primary_present = disc_detect(ATA_PIO_PRIMARY);
    boot_disc_primary_present = disc_detect(ATA_PIO_SECONDARY);

    if (boot_disc_primary_present) disc_reset(ATA_PIO_PRIMARY_CONTROL);
    if (boot_disc_secondary_present) disc_reset(ATA_PIO_SECONDARY_CONTROL);

    ata_pio_io_port_t * io_port;
    ata_pio_control_port_t * control_port;
    if (boot_disc_primary_present) {
        io_port = ATA_PIO_PRIMARY;
        control_port = ATA_PIO_PRIMARY_CONTROL;
    }
    else if (boot_disc_secondary_present) {
        io_port = ATA_PIO_SECONDARY;
        control_port = ATA_PIO_SECONDARY_CONTROL;
    }
    else return false;

    if (disc_select(io_port, DISC_SELECT_MASTER)) boot_disc_master_selected = true;
    else if (disc_select(io_port, DISC_SELECT_SLAVE)) boot_disc_master_selected = false;
    else return false;

    outb_ptr(&control_port->device_control, 0b10);

    console_newline();
    if (io_port == ATA_PIO_PRIMARY) console_print("PRIMARY\n");
    else console_print("SECONDARY\n");
    console_print("Master selected: ");
    console_print_bool(boot_disc_master_selected);
    console_newline();

    uint16_t data[256];
    memset(data, 0, sizeof(uint16_t) * 256);
    uint32_t error_value = disc_read28(
        io_port,
        boot_disc_master_selected ? DISC_READ28_MASTER : DISC_READ28_SLAVE,
        0,
        1,
        data
    );
    if (error_value) {
        console_print("ERROR: 0x");
        console_print_hex(error_value);
        console_newline();
        return false;
    }

    int index = 0;
    for (int i = 0; i < 256 / 6; i++) {
        for (int j = 0; j < 6; j++) {
            console_print(" 0x");
            console_print_hex(((uint8_t) data[index] & 0xF0) >> 4);
            console_print_hex((uint8_t) data[index] & 0x0F);
            console_print(" 0x");
            console_print_hex(((uint8_t) (data[index] >> 8) & 0xF0) >> 4);
            console_print_hex((uint8_t) (data[index] >> 8) & 0x0F);

            hlt();

            index++;
        }
        console_newline();
    }

    return true;
}