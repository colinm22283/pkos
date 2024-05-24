.code32

.global console_print_color
console_print_color:
    push %ebp
    mov  %esp, %ebp

    call clear_blinker

    mov   8(%esp), %eax
    mov  12(%esp), %dh

    movb (%eax), %dl
    test %dl,    %dl
    jz   .return
    cmp  $'\n',  %dl
    jne  .no_newline
        push %eax
        call console_newline
        pop  %eax
        movl (console_output_ptr), %ecx
        jmp  ..no_print
.no_newline:

    movl (console_output_ptr), %ecx

    .loop:
        movw %dx, (%ecx)

        add  $2, %ecx
    ..no_print:
        inc  %eax

        movb (%eax), %dl
        cmp  $'\n',  %dl
        jne  ..no_newline
            push %eax
            call console_newline
            pop  %eax
            movl (console_output_ptr), %ecx
            jmp ..no_print
    ..no_newline:
        test %dl,    %dl
        jnz  .loop

    movl %ecx, (console_output_ptr)

.return:
    call update_blinker

    pop %ebp
    ret
