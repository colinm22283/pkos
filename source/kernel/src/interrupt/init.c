#include <interrupt/init.h>
#include <interrupt/idt.h>
#include <interrupt/handlers.h>

#include <sys/asm/cli.h>
#include <sys/asm/sti.h>
#include <sys/asm/lidt.h>
#include <sys/asm/int.h>
#include <sys/asm/hlt.h>

void int_init(void) {
    idt.div0 = DEFINE_IDT64_ENTRY_INTERRUPT(int_handler_sys);

    for (unsigned char i = 0; i < 16; i++) {
//        idt.mapped_irqs = DEFI
    }

    idt.system_interrupt = DEFINE_IDT64_ENTRY_INTERRUPT(int_handler_sys);

    idt_ptr = DEFINE_IDT_POINTER(idt);

    cli();
    lidt(&idt_ptr);
    sti();

    asm_int(0x0);

    cli();

    hlt();
}