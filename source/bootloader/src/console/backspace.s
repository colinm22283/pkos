.code32

.global console_backspace
console_backspace:
    push %ebp
    mov  %esp, %ebp

    call clear_blinker

    movl (console_output_ptr), %eax
    sub  $2,                   %eax
    movb $' ',                 (%eax)
    movl %eax,                 (console_output_ptr)

    call update_blinker

    pop %ebp
    ret
