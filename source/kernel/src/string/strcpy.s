.code64

.section .text
.global strcpy
.type strcpy, @function
strcpy:
    .loop:
        movb (%rsi), %dl
        movb %dl,    (%rdi)

        inc %rsi
        inc %rdi

        test %dl, %dl
        jnz .loop

    ret
