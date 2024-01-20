#include <interrupt/init.h>
#include <interrupt/idt.h>

#include <interrupt/null_handler.h>
#include <interrupt/fatal_handler.h>
#include <interrupt/null_pic_handler_entry.h>
#include <interrupt/keyboard_handler_entry.h>

#include <pic/remap.h>
#include <pic/mask.h>

#include <sys/asm/lidt.h>
#include <sys/asm/sti.h>
#include <sys/asm/hlt.h>

void int_init(void) {
    pic_remap(0x20, 0x28);

    pic_set_mask(0);

    idt.div0                     = DEFINE_IDT32_ENTRY_INTERRUPT(int_fatal_handler);
    idt.nmi                      = DEFINE_IDT32_ENTRY_INTERRUPT(int_fatal_handler);
    idt.bp_int3                  = DEFINE_IDT32_ENTRY_INTERRUPT(int_null_handler);
    idt.ovf                      = DEFINE_IDT32_ENTRY_INTERRUPT(int_fatal_handler);
    idt.bound_range              = DEFINE_IDT32_ENTRY_INTERRUPT(int_fatal_handler);
    idt.invalid_opcode           = DEFINE_IDT32_ENTRY_INTERRUPT(int_fatal_handler);
    idt.device_not_avail         = DEFINE_IDT32_ENTRY_INTERRUPT(int_fatal_handler);
    idt.double_fault             = DEFINE_IDT32_ENTRY_INTERRUPT(int_fatal_handler);
    idt.coproc_segment_overrun   = DEFINE_IDT32_ENTRY_INTERRUPT(int_fatal_handler);
    idt.invalid_tss              = DEFINE_IDT32_ENTRY_INTERRUPT(int_fatal_handler);
    idt.segment_not_present      = DEFINE_IDT32_ENTRY_INTERRUPT(int_fatal_handler);
    idt.stack_segment_fault      = DEFINE_IDT32_ENTRY_INTERRUPT(int_fatal_handler);
    idt.general_protection_fault = DEFINE_IDT32_ENTRY_INTERRUPT(int_fatal_handler);
    idt.page_fault               = DEFINE_IDT32_ENTRY_INTERRUPT(int_fatal_handler);
    idt.x87_fpu_error            = DEFINE_IDT32_ENTRY_INTERRUPT(int_fatal_handler);
    idt.alignment_check          = DEFINE_IDT32_ENTRY_INTERRUPT(int_fatal_handler);
    idt.machine_check            = DEFINE_IDT32_ENTRY_INTERRUPT(int_fatal_handler);
    idt.simd_fp_error            = DEFINE_IDT32_ENTRY_INTERRUPT(int_fatal_handler);

    idt._res0 = DEFINE_IDT32_ENTRY_NULL;
    idt._res1 = DEFINE_IDT32_ENTRY_NULL;
    idt._res2 = DEFINE_IDT32_ENTRY_NULL;

    idt.mapped_irqs[0] = DEFINE_IDT32_ENTRY_INTERRUPT(int_null_pic1_handler_entry);
    idt.mapped_irqs[1] = DEFINE_IDT32_ENTRY_INTERRUPT(int_keyboard_handler_entry);
    for (uint16_t i = 2; i < 8; i++) idt.mapped_irqs[i] = DEFINE_IDT32_ENTRY_INTERRUPT(int_null_pic1_handler_entry);
    for (uint16_t i = 8; i < 16; i++) idt.mapped_irqs[i] = DEFINE_IDT32_ENTRY_INTERRUPT(int_null_pic2_handler_entry);

    lidt(&idt_ptr);
    sti();
}