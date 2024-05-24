.code32

.global console_print_dec
console_print_dec:
    push %ebp
    mov  %esp,    %ebp

    call clear_blinker

    mov  8(%esp), %eax

    push %ebx

    sub  $10,     %esp
    mov  %esp,    %ecx

    mov  $10, %ebx

    .decode_loop:
        xor  %edx, %edx

        div  %ebx

        add  $'0', %dl
        movb %dl,  (%ecx)
        inc  %ecx

        test %eax, %eax
        jnz .decode_loop

    movl (console_output_ptr), %eax

    .print_loop:
        dec  %ecx

        movb (%ecx), %dl
        movb %dl,    (%eax)
        add  $2,     %eax

        cmp  %ecx,   %esp
        jne  .print_loop

    movl %eax, (console_output_ptr)

    add  $10,     %esp

    pop  %ebx

    call update_blinker

    pop  %ebp
    ret
