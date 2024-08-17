#pragma once

#include <sys/idt/idt_ptr.h>
#include <sys/idt/idt64.h>

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
} idt_t;

extern idt_t idt;
extern idt_ptr_t idt_ptr;