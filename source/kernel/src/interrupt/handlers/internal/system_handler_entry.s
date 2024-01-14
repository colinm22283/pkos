.code64

.section .text
.global system_interrupt_handler_entry
system_interrupt_handler_entry:
    push %rcx
    push %rdx
    push %rdi
    push %rsi
    push %r8
    push %r9
    push %r10
    push %r11

    cld
    call system_interrupt_handler

    pop %r11
    pop %r10
    pop %r9
    pop %r8
    pop %rsi
    pop %rdi
    pop %rdx
    pop %rcx

    iretq
