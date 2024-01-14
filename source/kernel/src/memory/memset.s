.code64

.section .text, "a"
.global memset
.type memset, @function
memset:
    test %rdx, %rdx
    jz   .ret

    mov %rdx, %rcx
    .loop:
        movb %rsi,  (%rdi)

        inc  %rsi
        inc  %rdi

        loop .loop

    .ret:
    ret
