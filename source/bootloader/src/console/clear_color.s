.code32

.global console_clear_color
console_clear_color:
    push %ebp
    mov  %esp,    %ebp

    call clear_blinker

    xor  %al,        %al
    movb 8(%esp),    %ah
    mov  $(80 * 25), %ecx
    mov  $0xB8000,   %edx

    .loop:
        movw %ax, (%edx)

        add  $2,  %edx

        loop .loop

    mov $0xB8000,  %eax
    mov %eax,      (console_output_ptr)
    add $(80 * 2), %eax
    mov %eax,      (console_newline_ptr)

    pop %ebp
    ret
