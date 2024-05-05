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

    file_t kernel_file = open_file(root_directory, "kernel");
    if (kernel_file == 0) return false;

    filesystem_file_node_page_t file_page;
    if (disc_read48(io_port, boot_disc_master_selected ? DISC_READ48_MASTER : DISC_READ48_SLAVE, kernel_file, 1, (void *) &file_page)) return false;

    char * kernel_ptr = (char *) 0x100000;
    filesystem_page_address_t address = file_page.root_data_address;
    while (address != 0) {
        filesystem_file_data_page_t file_data;
        if (disc_read48(io_port, boot_disc_master_selected ? DISC_READ48_MASTER : DISC_READ48_SLAVE, address, 1, (void *) &file_data)) return false;

        memcpy(kernel_ptr, file_data.data, file_data.size);
        kernel_ptr += file_data.size;

        address = file_data.next_data_address;
    }

    return true;
}