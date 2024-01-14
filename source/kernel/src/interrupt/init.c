#include <stdbool.h>

#include <interrupt/init.h>
#include <interrupt/interrupts.h>

#include <idt.h>

void interrupt_init(void) {
    idt.div0                     = DEFINE_IDT_ENTRY_INTERRUPT(unimp_handler_entry);
    idt.nmi                      = DEFINE_IDT_ENTRY_INTERRUPT(unimp_handler_entry);
    idt.bp_int3                  = DEFINE_IDT_ENTRY_INTERRUPT(unimp_handler_entry);
    idt.ovf                      = DEFINE_IDT_ENTRY_INTERRUPT(unimp_handler_entry);
    idt.bound_range              = DEFINE_IDT_ENTRY_INTERRUPT(unimp_handler_entry);
    idt.invalid_opcode           = DEFINE_IDT_ENTRY_INTERRUPT(unimp_handler_entry);
    idt.device_not_avail         = DEFINE_IDT_ENTRY_INTERRUPT(unimp_handler_entry);
    idt.double_fault             = DEFINE_IDT_ENTRY_INTERRUPT(unimp_handler_entry);
    idt.coproc_segment_overrun   = DEFINE_IDT_ENTRY_INTERRUPT(unimp_handler_entry);
    idt.invalid_tss              = DEFINE_IDT_ENTRY_INTERRUPT(unimp_handler_entry);
    idt.segment_not_present      = DEFINE_IDT_ENTRY_INTERRUPT(unimp_handler_entry);
    idt.stack_segment_fault      = DEFINE_IDT_ENTRY_INTERRUPT(unimp_handler_entry);
    idt.general_protection_fault = DEFINE_IDT_ENTRY_INTERRUPT(gpf_handler_entry);
    idt.page_fault               = DEFINE_IDT_ENTRY_INTERRUPT(page_fault_handler_entry);
    idt.x87_fpu_error            = DEFINE_IDT_ENTRY_INTERRUPT(unimp_handler_entry);
    idt.alignment_check          = DEFINE_IDT_ENTRY_INTERRUPT(unimp_handler_entry);
    idt.machine_check            = DEFINE_IDT_ENTRY_INTERRUPT(unimp_handler_entry);
    idt.simd_fp_error            = DEFINE_IDT_ENTRY_INTERRUPT(unimp_handler_entry);

    idt.system_interrupt         = DEFINE_IDT_ENTRY_INTERRUPT(system_interrupt_handler_entry);

    for (uint16_t i = 0; i < 8; i++) idt.mapped_irqs[i] = DEFINE_IDT_ENTRY_INTERRUPT(null_pic1_handler_entry);
    for (uint16_t i = 8; i < 16; i++) idt.mapped_irqs[i] = DEFINE_IDT_ENTRY_INTERRUPT(null_pic2_handler_entry);

    asm ("lidt %0" :: "m"(idt_desc));
    asm ("sti");
}