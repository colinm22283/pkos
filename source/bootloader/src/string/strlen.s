.code32

.global strlen
strlen:
    push %ebp

    movl 8(%esp), %ecx
    xor  %ecx,    %eax

    movb (%ecx),  %dl
    test %dl,     %dl
    jz   .exit
    .loop:
        inc  %eax
        inc  %ecx

        movb (%ecx),  %dl
        test %dl,     %dl
        jnz   .loop

    .exit:
    pop  %ebp
    ret