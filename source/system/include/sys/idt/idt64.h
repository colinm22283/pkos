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
} idt64_entry_t;

typedef struct __PACKED {
    idt64_entry_t
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

    idt64_entry_t _undefined_entries0[11];

    idt64_entry_t mapped_irqs[16];

    idt64_entry_t _undefined_entries1[80];

    idt64_entry_t system_interrupt;
} idt32_t;

#define DEFINE_IDT64_ENTRY_INTERRUPT(handler) ((idt64_entry_t) {     \
    .offset_lower = (uint16_t) (((uint32_t) &handler) & 0xFFFF), \
    .offset_upper = ((uint32_t) &handler) >> 16,                 \
    .ist = 0,                                                    \
    .dpl = 0,                                                    \
    .p = 1,                                                      \
    .gate_type = 0xE,                                            \
    .selector = GDT_CODE_SEG,                                    \
    ._reserved0 = 0,                                             \
    ._reserved1 = 0,                                             \
    ._reserved2 = 0,                                             \
})

#define DEFINE_IDT64_ENTRY_TRAP(handler) ((idt64_entry_t) {               \
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

#define DEFINE_IDT64_ENTRY_NULL ((idt64_entry_t) { \
    .offset_lower = 0, \
    .offset_upper = 0, \
    .ist = 0,          \
    .dpl = 0,          \
    .p = 0,            \
    .gate_type = 0,    \
    .selector = 0,     \
    ._reserved0 = 0,   \
    ._reserved1 = 0,   \
    ._reserved2 = 0,   \
})
