#include <sys/halt.h>

typedef enum {
    SYSTEM = 0,
    DIV0 = 1,
} int_handler_type_t;

void int_handler(int_handler_type_t interrupt_type) {
    halt();
}