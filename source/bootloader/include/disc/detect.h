#pragma once

#include <stdbool.h>

#include <sys/ata/pio.h>

bool disc_detect(ata_pio_io_port_t * io_port);