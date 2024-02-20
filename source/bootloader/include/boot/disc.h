#pragma once

#include <stdbool.h>

extern bool boot_disc_primary_present;
extern bool boot_disc_secondary_present;
extern bool boot_disc_master_selected;

bool boot_disc_init();