#pragma once

#include <stdint.h>

#include <defs.h>

enum {
    ATA_PIO_COMMAND_READ     = 0x20,
    ATA_PIO_COMMAND_READ_EXT = 0x24,
    ATA_PIO_COMMAND_IDENTIFY = 0xEC,
};

typedef struct {
    uint8_t address_mark_not_found      : 1;
    uint8_t track_zero_not_found        : 1;
    uint8_t aborted_command             : 1;
    uint8_t media_change_request        : 1;
    uint8_t id_not_found                : 1;
    uint8_t media_changed               : 1;
    uint8_t uncorrectable_data_error    : 1;
    uint8_t bad_block_detected          : 1;
} __PACKED ata_pio_error_t;

typedef struct {
    uint8_t address      : 4; // In CHS addressing, bits 0 to 3 of the head. In LBA addressing, bits 24 to 27 of the block number.
    uint8_t drive_number : 1;
    uint8_t _always_set0 : 1;
    uint8_t lba_enable   : 1;
    uint8_t _always_set1 : 1;
} __PACKED apa_pio_drive_head_t;

typedef struct {
    uint8_t error           : 1;
    uint8_t index           : 1; // always zero
    uint8_t corrected_data  : 1; // always zero
    uint8_t data_ready      : 1;
    uint8_t service_request : 1;
    uint8_t drive_fault     : 1; // does not set error
    uint8_t ready           : 1;
    uint8_t busy            : 1;
} __PACKED ata_pio_status_t;

typedef struct {
    uint8_t _always_zero      : 1;
    uint8_t interrupt_disable : 1;
    uint8_t software_reset    : 1;
    uint8_t _reserved         : 4;
    uint8_t hob               : 1;
} __PACKED ata_pio_device_control_t;
enum {
    ATA_PIO_DEVICE_CONTROL_INTERRUPT_DISABLE = 1 << 1,
    ATA_PIO_DEVICE_CONTROL_SOFTWARE_RESET    = 1 << 2,
    ATA_PIO_DEVICE_CONTROL_HOB               = 1 << 7,
};

typedef struct {
    uint8_t drive_zero_select : 1;
    uint8_t drive_one_select  : 1;
    uint8_t head_select_2c    : 4;
    uint8_t write_gate        : 1;
    uint8_t _reserved         : 1;
} __PACKED ata_pio_drive_address_t;

typedef struct {
    uint8_t data;
    union {
        uint8_t error;
        uint8_t features;
    };
    uint8_t sector_count;
    union {
        uint8_t sector_number;
        uint8_t lba_low;
    };
    union {
        uint8_t cylinder_low;
        uint8_t lba_mid;
    };
    union {
        uint8_t cylinder_high;
        uint8_t lba_high;
    };
    uint8_t drive_head;
    union {
        uint8_t status;
        uint8_t command;
    };
} ata_pio_io_port_t;

typedef struct {
    union {
        uint8_t status;
        uint8_t device_control;
    };
    uint8_t drive_access;
} ata_pio_control_port_t;