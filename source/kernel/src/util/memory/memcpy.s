.code64

.global memcpy
memcpy:
    mov  %edx,     %ecx

    test %ecx,     %ecx
    jz   .ret

    .loop:
        movb (%rsi), %dl
        movb %dl,    (%rdi)

        inc  %rsi
        inc  %rdi

        loop .loop

.ret:
    ret
