.code64

.global strcmp
strcmp:
    xor %rax, %rax
    xor %rdx, %rdx
    .loop:
        movb (%rdi), %al
        inc  %rdi

        test %al, %al
        jz   .return

        movb (%rsi), %dl
        inc  %rsi

        test %dl, %dl
        jz   .return

        sub  %rdx, %rax
        jz   .loop

    .return:
    ret
