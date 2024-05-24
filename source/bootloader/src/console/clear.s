.code32

.global console_clear
console_clear:
    push %ebp
    mov  %esp, %ebp

    call clear_blinker

    mov  $0xB8000,   %eax
    mov  $(80 * 25), %ecx
    .loop:
        movb $0x00, (%eax)
        add  $2,    %eax

        loop .loop

    mov $0xB8000,  %eax
    mov %eax,      (console_output_ptr)
    add $(80 * 2), %eax
    mov %eax,      (console_newline_ptr)

    pop  %ebp
    ret
