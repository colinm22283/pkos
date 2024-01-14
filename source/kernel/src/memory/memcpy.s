.code64

.section .text, "a"
.global memcpy
.type memcpy, @function
memcpy:
    test %rdx, %rdx
    jz   .ret

    mov %rdx, %rcx
    .loop:
        movb (%rsi), %dl
        movb %dl,    (%rdi)

        inc %rsi
        inc %rdi

        loop .loop

    .ret:
    ret
