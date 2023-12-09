#pragma once

#include <stdint.h>

typedef struct {
    uint16_t size;
    void * offset;
} idt_desc_t;

#define DEFINE_IDT_DESCRIPTOR(idt) { .size = sizeof(idt) - 1, .offset = &idt, }