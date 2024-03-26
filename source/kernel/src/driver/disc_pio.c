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

enum {
    DRIVER_OK,
    DRIVER_ERROR_ADDRESS_MARK_NOT_FOUND,
    DRIVER_ERROR_TRACK_ZERO_NOT_FOUND,
    DRIVER_ERROR_ABORTED_COMMAND,
    DRIVER_ERROR_MEDIA_CHANGE_REQUEST,
    DRIVER_ERROR_ID_NOT_FOUND,
    DRIVER_ERROR_MEDIA_CHANGED,
    DRIVER_ERROR_UNCORRECTABLE_DATA_ERROR,
    DRIVER_ERROR_BAD_BLOCK_DETECTED,
    DRIVER_ERROR_UNKNOWN,
};

uint8_t selected_device;
uint8_t devices_count;
device_t devices[4];

uint8_t current_error;

static inline bool wait_ready(ata_pio_io_port_t * io_port) {
    union { uint8_t uint8; ata_pio_status_t value; } status = { .uint8 = inb_ptr(&io_port->status), };
    while ((status.value.busy || !status.value.ready) && !status.value.error) status.uint8 = inb_ptr(&io_port->status);
    if (status.value.error) return false;

    return true;
}

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

static inline void set_current_error(ata_pio_io_port_t * io_port) {
    union { uint8_t num; ata_pio_error_t error; } error_value = { .num = inb_ptr(&io_port->error), };

    if (error_value.error.aborted_command) current_error = DRIVER_ERROR_ABORTED_COMMAND;
    else if (error_value.error.address_mark_not_found) current_error = DRIVER_ERROR_ADDRESS_MARK_NOT_FOUND;
    else if (error_value.error.bad_block_detected) current_error = DRIVER_ERROR_BAD_BLOCK_DETECTED;
    else if (error_value.error.id_not_found) current_error = DRIVER_ERROR_ID_NOT_FOUND;
    else if (error_value.error.media_change_request) current_error = DRIVER_ERROR_MEDIA_CHANGE_REQUEST;
    else if (error_value.error.media_changed) current_error = DRIVER_ERROR_MEDIA_CHANGED;
    else if (error_value.error.track_zero_not_found) current_error = DRIVER_ERROR_TRACK_ZERO_NOT_FOUND;
    else if (error_value.error.uncorrectable_data_error) current_error = DRIVER_ERROR_UNCORRECTABLE_DATA_ERROR;
    else current_error = DRIVER_ERROR_UNKNOWN;
}

enum {
    DEVICE_DETECT_DRIVE_ID_MASTER = 0xA0,
    DEVICE_DETECT_DRIVE_ID_SLAVE = 0xB0,
};
static inline bool device_detect(ata_pio_io_port_t * io_port, uint8_t drive_id) {
    current_error = DRIVER_OK;

    outb_ptr(&io_port->drive_head, drive_id);
    outb_ptr(&io_port->lba_low, 0);
    outb_ptr(&io_port->lba_mid, 0);
    outb_ptr(&io_port->lba_high, 0);
    outb_ptr(&io_port->command, ATA_PIO_COMMAND_IDENTIFY);

    for (int i = 0; i < 256; i++) {
        if (!wait_ready(io_port)) {
            set_current_error(io_port);
            return false;
        }

        inw_ptr(&io_port->data);
    }

    if (!wait_ready(io_port)) {
        set_current_error(io_port);
        return false;
    }

    return true;
}

static inline bool disc_reset(ata_pio_io_port_t * io_port, ata_pio_control_port_t * control_port) {
    outb_ptr(&control_port->device_control, ATA_PIO_DEVICE_CONTROL_SOFTWARE_RESET);
    outb_ptr(&control_port->device_control, 0);

    inb_ptr(&control_port->status);
    inb_ptr(&control_port->status);
    inb_ptr(&control_port->status);
    inb_ptr(&control_port->status);

    if (!wait_ready(io_port)) {
        set_current_error(io_port);
        return false;
    }

    return true;
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

    outb_ptr(&io_port->command, ATA_PIO_COMMAND_READ);

    for (int i = 0; i < sector_count; i++) {
        if (!wait_ready(io_port)) {
            set_current_error(io_port);
            return false;
        }

        for (int j = 0; j < 256; j++) {
            *dest = inw_ptr(&io_port->data);

            dest++;

            if (!wait_ready(io_port)) {
                set_current_error(io_port);
                return false;
            }
        }
    }
    if (!wait_ready(io_port)) {
        set_current_error(io_port);
        return false;
    }

    return true;
}
static inline bool write28(ata_pio_io_port_t * io_port, uint8_t drive_select, uint64_t lba, uint16_t sector_count, uint16_t * src) {
    if (lba > 0xFFFFFF) return false;

    outb_ptr(&io_port->drive_head, drive_select | ((lba >> 24) & 0xF));

    outb_ptr(&io_port->sector_count, sector_count);

    outb_ptr(&io_port->lba_low, lba);
    outb_ptr(&io_port->lba_mid, lba >> 8);
    outb_ptr(&io_port->lba_high, lba >> 16);

    outb_ptr(&io_port->command, ATA_PIO_COMMAND_WRITE);

    for (int i = 0; i < sector_count; i++) {
        if (!wait_ready(io_port)) {
            set_current_error(io_port);
            return false;
        }

        for (int j = 0; j < 256; j++) {
            outw_ptr(&io_port->data, *src);

            src++;

            if (!wait_ready(io_port)) {
                set_current_error(io_port);
                return false;
            }
        }

        outb_ptr(&io_port->command, ATA_PIO_COMMAND_CACHE_FLUSH);
    }

    if (!wait_ready(io_port)) {
        set_current_error(io_port);
        return false;
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

    for (int i = 0; i < sector_count; i++) {
        if (!wait_ready(io_port)) {
            set_current_error(io_port);
            return false;
        }

        for (int j = 0; j < 256; j++) {
            *dest = inw_ptr(&io_port->data);

            dest++;

            if (!wait_ready(io_port)) {
                set_current_error(io_port);
                return false;
            }
        }
    }

    if (!wait_ready(io_port)) {
        set_current_error(io_port);
        return false;
    }

    return true;
}

static inline bool write48(ata_pio_io_port_t * io_port, uint8_t drive_select, uint64_t lba, uint16_t sector_count, uint16_t * src) {
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
    outb_ptr(&io_port->command, ATA_PIO_COMMAND_WRITE_EXT);

    for (int i = 0; i < sector_count; i++) {
        if (!wait_ready(io_port)) {
            set_current_error(io_port);
            return false;
        }

        for (int j = 0; j < 256; j++) {
            outw_ptr(&io_port->data, *src);

            src++;

            if (!wait_ready(io_port)) {
                set_current_error(io_port);
                return false;
            }
        }
    }

    if (!wait_ready(io_port)) {
        set_current_error(io_port);
        return false;
    }

    return true;
}

uint16_t device_count() {
    current_error = DRIVER_OK;

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
    current_error = DRIVER_OK;

    if (device >= devices_count) return false;

    selected_device = device;

    return disc_reset(device_io_port(), device_control_port());
}

bool read(uint32_t lba, uint16_t sector_count, void * dst) {
    current_error = DRIVER_OK;

    ata_pio_io_port_t * io_port = device_io_port();

    if (lba > 0xFFFFFF || sector_count > 0xFF) {
        return read48(
            io_port,
            devices[selected_device].drive == DEVICE_DRIVE_MASTER ? READ48_DRIVE_SELECT_MASTER : READ48_DRIVE_SELECT_SLAVE,
            lba,
            sector_count,
            dst
        );
    }
    else {
        return read28(
            io_port,
            devices[selected_device].drive == DEVICE_DRIVE_MASTER ? READ28_DRIVE_SELECT_MASTER : READ28_DRIVE_SELECT_SLAVE,
            lba,
            sector_count,
            dst
        );
    }
}

bool write(uint32_t lba, uint16_t sector_count, void * src) {
    current_error = DRIVER_OK;

    ata_pio_io_port_t * io_port = device_io_port();

    if (lba > 0xFFFFFF || sector_count > 0xFF) {
        return write48(
            io_port,
            devices[selected_device].drive == DEVICE_DRIVE_MASTER ? READ48_DRIVE_SELECT_MASTER : READ48_DRIVE_SELECT_SLAVE,
            lba,
            sector_count,
            src
        );
    }
    else {
        return write28(
            io_port,
            devices[selected_device].drive == DEVICE_DRIVE_MASTER ? READ28_DRIVE_SELECT_MASTER : READ28_DRIVE_SELECT_SLAVE,
            lba,
            sector_count,
            src
        );
    }
}

const char * get_error_string() {
    switch (current_error) {
        case DRIVER_OK: return "OK";
        case DRIVER_ERROR_ADDRESS_MARK_NOT_FOUND: return "ADDRESS MARK NOT FOUND";
        case DRIVER_ERROR_TRACK_ZERO_NOT_FOUND: return "TRACK ZERO NOT FOUND";
        case DRIVER_ERROR_ABORTED_COMMAND: return "ABORTED COMMAND";
        case DRIVER_ERROR_MEDIA_CHANGE_REQUEST: return "MEDIA CHANGE REQUEST";
        case DRIVER_ERROR_ID_NOT_FOUND: return "ID NOT FOUND";
        case DRIVER_ERROR_MEDIA_CHANGED: return "MEDIA CHANGED";
        case DRIVER_ERROR_UNCORRECTABLE_DATA_ERROR: return "UNCORRECTABLE DATA ERROR";
        case DRIVER_ERROR_BAD_BLOCK_DETECTED: return "BAD BLOCK DETECTED";
        default: return "UNKNOWN";
    }
}

bool disc_pio_start() {
    current_error = DRIVER_OK;

    return true;
}
bool disc_pio_stop() { return true; }

void driver_disc_pio_load(driver_table_t * dt) {
    dt->disc.start = disc_pio_start;
    dt->disc.stop  = disc_pio_stop;

    dt->disc.device_count = device_count;
    dt->disc.select_device = select_device;

    dt->disc.get_error_string = get_error_string;

    dt->disc.read = read;
    dt->disc.write = write;
}