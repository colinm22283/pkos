.code64

.section .text
.global page_fault_handler_entry
page_fault_handler_entry:
    push %rax
    push %rcx
    push %rdx
    push %rdi
    push %rsi
    push %r8
    push %r9
    push %r10
    push %r11

    cld
    call page_fault_handler

    pop %r11
    pop %r10
    pop %r9
    pop %r8
    pop %rsi
    pop %rdi
    pop %rdx
    pop %rcx
    pop %rax

    iretq
