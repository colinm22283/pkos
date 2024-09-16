#pragma once

#include <stdbool.h>
#include <stdint.h>

extern bool boot_disc_primary_present;
extern bool boot_disc_secondary_present;
extern bool boot_disc_master_selected;

bool boot_disc_init();
bool boot_disc_load_kernel(uint64_t kernel_load_point);