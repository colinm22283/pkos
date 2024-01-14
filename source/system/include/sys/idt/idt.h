#pragma once

#include <stdint.h>

#include <defs.h>

typedef struct __PACKED {
    uint16_t offset_lower : 16;
    uint16_t selector     : 16;
    uint8_t  ist          :  3;
    uint8_t  _reserved0   :  5;
    uint8_t  gate_type    :  4;
    uint8_t  _reserved1   :  1;
    uint8_t  dpl          :  2;
    uint8_t  p            :  1;
    uint64_t offset_upper : 48;
    uint32_t _reserved2   : 32;
} idt_entry_t;

typedef struct __PACKED {
    idt_entry_t
        div0,
        _res0,
        nmi,
        bp_int3,
        ovf,
        bound_range,
        invalid_opcode,
        device_not_avail,
        double_fault,
        coproc_segment_overrun,
        invalid_tss,
        segment_not_present,
        stack_segment_fault,
        general_protection_fault,
        page_fault,
        _res1,
        x87_fpu_error,
        alignment_check,
        machine_check,
        simd_fp_error,
        _res2;

    idt_entry_t _undefined_entries0[11];

    idt_entry_t mapped_irqs[16];

    idt_entry_t _undefined_entries1[80];

    idt_entry_t system_interrupt;

//    idt_entry_t _undefined_entries1[100];
} idt_t;

#define DEFINE_IDT_ENTRY_INTERRUPT(handler) ((idt_entry_t) {     \
    .offset_lower = (uint16_t) (((uint64_t) &handler) & 0xFFFF), \
    .offset_upper = ((uint64_t) &handler) >> 16,                 \
    .ist = 0,                                                    \
    .dpl = 0,                                                    \
    .p = 1,                                                      \
    .gate_type = 0xE,                                            \
    .selector = GDT_CODE_SEG,                                    \
    ._reserved0 = 0,                                             \
    ._reserved1 = 0,                                             \
    ._reserved2 = 0,                                             \
})

#define DEFINE_IDT_ENTRY_TRAP(handler) ((idt_entry_t) {               \
    .offset_lower = (uint16_t) (((uint64_t) &handler) & 0xFFFF), \
    .offset_upper = ((uint64_t) &handler) << 16,                 \
    .ist = 0,                                                    \
    .dpl = 0,                                                    \
    .p = 1,                                                      \
    .gate_type = 0xF,                                            \
    .selector = GDT_CODE_SEG,                                    \
    ._reserved0 = 0,                                             \
    ._reserved1 = 0,                                             \
    ._reserved2 = 0,                                             \
})

