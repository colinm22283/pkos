#include <disc/detect.h>

#include <sys/asm/in.h>
#include <sys/ata/pio.h>

bool disc_detect(const ata_pio_io_port_t * io_port) {
    return inb_ptr(&io_port->status) != 0xFF;
}