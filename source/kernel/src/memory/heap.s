.code64

.section .text, "a"
.global sys_heap_init
sys_heap_init:
    mov $_heap_base, %rax
    movl $0, (%rax)
    movl $(0x500 - 16), 4(%rax)

    mov $(_heap_top - 8), %rax
    movl $0, (%rax)
    movl $0, 4(%rax)

    ret

.global sys_heap_alloc
sys_heap_alloc:
    push %rbx

    pop %rbx
    ret

.global sys_heap_free
sys_heap_free:
    ret