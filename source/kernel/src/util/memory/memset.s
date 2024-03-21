.code64

.global memset
memset:
    mov %rsi, %rdx
    mov %rdx, %rcx

    test %rcx,     %rcx
    jz   .ret

    .loop:
        movb %dl, (%rdi)
        inc  %rdi

        loop .loop

.ret:
    ret
