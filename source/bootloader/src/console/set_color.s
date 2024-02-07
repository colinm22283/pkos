.code32

.global console_set_color
console_set_color:
    push %ebp
    mov  %esp,    %ebp

    movb 8(%esp),    %al
    mov  $(80 * 25), %ecx
    mov  $0xB8001,   %edx

    .loop:
        movb %al, (%edx)
        add  $2,  %edx

        loop .loop

    pop  %ebp
    ret
