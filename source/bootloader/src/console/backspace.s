.code32

.global console_backspace
console_backspace:
    push %ebp
    mov  %esp, %ebp

    movl (console_output_ptr), %eax
    sub  $2,                   %eax
    movb $' ',                 (%eax)
    movl %eax,                 (console_output_ptr)

    pop %ebp
    ret
