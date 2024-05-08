#include <boot/disc.h>
#include <boot/kernel.h>

#include <disc/detect.h>
#include <disc/reset.h>
#include <disc/select.h>
#include <disc/read.h>
#include <disc/filesystem.h>

#include <sys/ports.h>

#include <console/print.h>
#include <console/print_hex.h>
#include <console/newline.h>
#include <console/print_bool.h>

#include <sys/asm/hlt.h>
#include <sys/asm/out.h>

#include <memory/memset.h>
#include <memory/memcpy.h>

bool boot_disc_primary_present;
bool boot_disc_secondary_present;
bool boot_disc_master_selected;

ata_pio_io_port_t * io_port;
ata_pio_control_port_t * control_port;

bool boot_disc_init() {
    boot_disc_primary_present = disc_detect(ATA_PIO_PRIMARY);
    boot_disc_secondary_present = disc_detect(ATA_PIO_SECONDARY);

    if (boot_disc_primary_present) disc_reset(ATA_PIO_PRIMARY_CONTROL);
    if (boot_disc_secondary_present) disc_reset(ATA_PIO_SECONDARY_CONTROL);

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

    return true;
}

bool boot_disc_load_kernel() {
    directory_t root_directory = open_filesystem(KERNEL_LBA_START);
    if (root_directory == 0) return false;

    directory_t boot_directory = open_directory(root_directory, "boot");
    if (boot_directory == 0) return false;

    file_t kernel_file = open_file(boot_directory, "kernel");
    if (kernel_file == 0) return false;

    file_reader_t reader;
    if (!file_reader_init(&reader, kernel_file)) return false;

    char * kernel_ptr = (char *) 0x100000; // TODO: make sure this is free
    uint64_t read_bytes;
    while ((read_bytes = file_reader_read(&reader, kernel_ptr, FILESYSTEM_FILE_DATA_PAGE_SIZE))) {
        kernel_ptr += read_bytes;
    }

    return true;
}