#include <stddef.h>

#include <driver/disc_pio.h>

#include <sys/asm/in.h>
#include <sys/asm/out.h>
#include <sys/ata/pio.h>
#include <sys/ports.h>

#define PRIMARY_IO_PORT ((ata_pio_io_port_t *) ATA_PIO_PRIMARY)
#define SECONDARY_IO_PORT ((ata_pio_io_port_t *) ATA_PIO_SECONDARY)
#define PRIMARY_CONTROL_PORT ((ata_pio_control_port_t *) ATA_PIO_PRIMARY_CONTROL)
#define SECONDARY_CONTROL_PORT ((ata_pio_control_port_t *) ATA_PIO_SECONDARY_CONTROL)

enum { DEVICE_BUS_PRIMARY, DEVICE_BUS_SECONDARY };
enum { DEVICE_DRIVE_MASTER, DEVICE_DRIVE_SLAVE };
typedef struct {
    uint8_t bus;
    uint8_t drive;
} device_t;

uint8_t selected_device;
uint8_t devices_count;
device_t devices[4];

static inline ata_pio_io_port_t * device_io_port() {
    switch (devices[selected_device].bus) {
        case DEVICE_BUS_PRIMARY: return PRIMARY_IO_PORT;
        case DEVICE_BUS_SECONDARY: return SECONDARY_IO_PORT;
        default: return NULL;
    }
}

static inline ata_pio_control_port_t * device_control_port() {
    switch (devices[selected_device].bus) {
        case DEVICE_BUS_PRIMARY: return PRIMARY_CONTROL_PORT;
        case DEVICE_BUS_SECONDARY: return SECONDARY_CONTROL_PORT;
        default: return NULL;
    }
}

enum {
    DEVICE_DETECT_DRIVE_ID_MASTER = 0xA0,
    DEVICE_DETECT_DRIVE_ID_SLAVE = 0xB0,
};
static inline bool device_detect(ata_pio_io_port_t * io_port, uint8_t drive_id) {
    outb_ptr(&io_port->drive_head, drive_id);
    outb_ptr(&io_port->lba_low, 0);
    outb_ptr(&io_port->lba_mid, 0);
    outb_ptr(&io_port->lba_high, 0);
    outb_ptr(&io_port->command, ATA_PIO_COMMAND_IDENTIFY);

    union { uint8_t uint8; ata_pio_status_t value; } status = { .uint8 = inb_ptr(&io_port->status), };
    for (int i = 0; i < 256; i++) {
        while ((status.value.busy) && !status.value.error) status.uint8 = inb_ptr(&io_port->status);
        if (status.value.error) {
            return false;
        }

        inw_ptr(&io_port->data);
    }

    return true;
}

static inline void disc_reset(ata_pio_control_port_t * control_port) {
    outb_ptr(&control_port->device_control, ATA_PIO_DEVICE_CONTROL_SOFTWARE_RESET);
    outb_ptr(&control_port->device_control, 0);

    inb_ptr(&control_port->status);
    inb_ptr(&control_port->status);
    inb_ptr(&control_port->status);
    inb_ptr(&control_port->status);

    union { uint8_t uint8; ata_pio_status_t value; } status = { .uint8 = inb_ptr(&control_port->status), };
    while ((status.value.busy) && !status.value.error) status.uint8 = inb_ptr(&control_port->status);
}

enum {
    READ28_DRIVE_SELECT_MASTER = 0xE0,
    READ28_DRIVE_SELECT_SLAVE  = 0xF0,
};
static inline bool read28(ata_pio_io_port_t * io_port, uint8_t drive_select, uint64_t lba, uint16_t sector_count, uint16_t * dest) {
    if (lba > 0xFFFFFF) return false;

    outb_ptr(&io_port->drive_head, drive_select | ((lba >> 24) & 0xF));

    outb_ptr(&io_port->sector_count, sector_count);

    outb_ptr(&io_port->lba_low, lba);
    outb_ptr(&io_port->lba_mid, lba >> 8);
    outb_ptr(&io_port->lba_high, lba >> 16);

    outb(0x1F7, ATA_PIO_COMMAND_READ);

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

    return true;
}

enum {
    READ48_DRIVE_SELECT_MASTER = 0x40,
    READ48_DRIVE_SELECT_SLAVE  = 0x50,
};
static inline bool read48(ata_pio_io_port_t * io_port, uint8_t drive_select, uint64_t lba, uint16_t sector_count, uint16_t * dest) {
    if (lba > 0xFFFFFFFFFFFF) return false;

    outb_ptr(&io_port->drive_head, drive_select);

    outb_ptr(&io_port->sector_count, sector_count >> 8);
    outb_ptr(&io_port->lba_low, lba >> 24);
    outb_ptr(&io_port->lba_mid, lba >> 32);
    outb_ptr(&io_port->lba_high, lba >> 40);
    outb_ptr(&io_port->sector_count, sector_count & 0xFF);
    outb_ptr(&io_port->lba_low, lba >> 0);
    outb_ptr(&io_port->lba_mid, lba >> 8);
    outb_ptr(&io_port->lba_high, lba >> 16);
    outb_ptr(&io_port->command, ATA_PIO_COMMAND_READ_EXT);

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

    return true;
}

uint16_t device_count() {
    uint16_t count = 0;

    bool primary_present = inb_ptr(&PRIMARY_IO_PORT->status) != 0xFF;
    bool secondary_present = inb_ptr(&SECONDARY_IO_PORT->status) != 0xFF;

    if (primary_present) {
        if (device_detect(PRIMARY_IO_PORT, DEVICE_DETECT_DRIVE_ID_MASTER)) {
            devices[count++] = (device_t) {
                .bus = DEVICE_BUS_PRIMARY,
                .drive = DEVICE_DRIVE_MASTER,
            };
        }
        if (device_detect(PRIMARY_IO_PORT, DEVICE_DETECT_DRIVE_ID_SLAVE)) {
            devices[count++] = (device_t) {
                .bus = DEVICE_BUS_PRIMARY,
                .drive = DEVICE_DRIVE_SLAVE,
            };
        }
    }
    if (secondary_present) {
        if (device_detect(SECONDARY_IO_PORT, DEVICE_DETECT_DRIVE_ID_MASTER)) {
            devices[count++] = (device_t) {
                .bus = DEVICE_BUS_SECONDARY,
                .drive = DEVICE_DRIVE_MASTER,
            };
        }
        if (device_detect(SECONDARY_IO_PORT, DEVICE_DETECT_DRIVE_ID_SLAVE)) {
            devices[count++] = (device_t) {
                .bus = DEVICE_BUS_SECONDARY,
                .drive = DEVICE_DRIVE_SLAVE,
            };
        }
    }

    selected_device = 0;
    devices_count = count;

    return count;
}

bool select_device(uint16_t device) {
    if (device >= devices_count) return false;

    selected_device = device;

    disc_reset(device_control_port());

    return true;
}

bool read(uint32_t lba, uint16_t sector_count, void * dest) {
    ata_pio_io_port_t * io_port = device_io_port();

    if (lba > 0xFFFFFF || sector_count > 0xFF) {
        return read48(
            io_port,
            devices[selected_device].drive == DEVICE_DRIVE_MASTER ? READ48_DRIVE_SELECT_MASTER : READ48_DRIVE_SELECT_SLAVE,
            lba,
            sector_count,
            dest
        );
    }
    else {
        return read28(
            io_port,
            devices[selected_device].drive == DEVICE_DRIVE_MASTER ? READ28_DRIVE_SELECT_MASTER : READ28_DRIVE_SELECT_SLAVE,
            lba,
            sector_count,
            dest
        );
    }
}

const char * get_error_string() {
    return NULL;
}

bool disc_pio_start() { return true; }
bool disc_pio_stop() { return true; }

void driver_disc_pio_load(driver_table_t * dt) {
    dt->disc.start = disc_pio_start;
    dt->disc.stop  = disc_pio_stop;

    dt->disc.device_count = device_count;
    dt->disc.select_device = select_device;

    dt->disc.get_error_string = get_error_string;

    dt->disc.read = read;
}