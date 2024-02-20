#pragma once

#include <stdint.h>

#include <sys/ata/pio.h>

enum {
    DISC_READ28_MASTER = 0xE0,
    DISC_READ28_SLAVE  = 0xF0,
};

uint32_t disc_read28(ata_pio_io_port_t * io_port, uint8_t drive_select, uint32_t lba, uint8_t sector_count, uint16_t * dest);