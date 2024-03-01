#include <stdint.h>

#include <defs.h>

#include <sys/halt.h>

#include <driver/disc_pio.h>

__NORETURN __SECTION(".kernel_entry") void kernel_entry() {
    driver_disc_pio_load(&driver_table);
    driver_table.disc.start();

    uint16_t device_count = driver_table.disc.device_count();

    driver_table.disc.select_device(0);

    driver_table.disc.read(0, 1, (void *) 0xB8000);

    driver_table.disc.stop();

    halt();
}