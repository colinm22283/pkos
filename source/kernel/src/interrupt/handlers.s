.code64

.global int_handler_div0
int_handler_div0:
    push %rax
    push %rcx
    push %rdx
    push %rdi
    push %rsi

    cld
    mov $1, %rax
    call int_handler

    pop %rsi
    pop %rdi
    pop %rdx
    pop %rcx
    pop %rax

    iret

.global int_handler_pic1
int_handler_pic1:



.global int_handler_pic2

.global int_handler_sys
int_handler_sys:
    push %rax
    push %rcx
    push %rdx
    push %rdi
    push %rsi

    cld
    xor %rax, %rax
    call int_handler

    pop %rsi
    pop %rdi
    pop %rdx
    pop %rcx
    pop %rax

    iret