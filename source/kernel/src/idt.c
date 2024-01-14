#include <idt.h>

idt_t idt;
idt_ptr_t idt_desc = DEFINE_IDT_DESCRIPTOR(idt);