.code32

.global console_print_hex
console_print_hex:
    push %ebp
    mov  %esp,    %ebp

    call clear_blinker

    xor  %ecx,    %ecx

    movl 8(%esp), %eax

    sub  $8,      %esp
    mov  %esp,    %edx

    .decode_loop:
        mov  %al,  %cl
        and  $0xF, %cl
        movb %cl,  (%edx)
        inc  %edx

        shr  $4,   %eax

        test %eax, %eax
        jnz  .decode_loop

    mov  (console_output_ptr), %eax
    .print_loop:
        dec %edx

        movb (%edx),    %cl
        add  $.hex_lut, %ecx
        movb (%ecx),    %cl
        movb %cl,       (%eax)
        xor  %ecx,      %ecx
        add  $2,        %eax

        cmp %edx, %esp
        jne .print_loop

    add  $8,   %esp

    movl %eax, (console_output_ptr)

    call update_blinker

    pop  %ebp
    ret

    .hex_lut: .string "0123456789ABCDEF"
