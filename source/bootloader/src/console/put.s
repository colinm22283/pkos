.code32

.global console_put
console_put:
    push %ebp
    mov  %esp, %ebp

    call clear_blinker

    movb 8(%esp), %cl

    movl (console_output_ptr), %eax
    movb %cl,                  (%eax)
    add  $2,                   %eax
    movl %eax,                 (console_output_ptr)

    call update_blinker

    pop %ebp
    ret
