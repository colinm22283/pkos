.code32

.global console_print_sdec
console_print_sdec:
    push %ebp

    mov  8(%esp), %eax
    test %eax,    %eax
    jns  .non_neg
        push $'-'
        call console_put
        add  $4, %esp

        xor  %eax,    %eax
        mov  8(%esp), %ecx
        sub  %ecx,    %eax
        push %eax
        call console_print_dec
        add  $4, %esp

        pop  %ebp
        ret
    .non_neg:

    push %eax
    call console_print_dec
    add  $4, %esp

    pop  %ebp
    ret
