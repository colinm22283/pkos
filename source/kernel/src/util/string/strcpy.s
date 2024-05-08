.code64

.global strcpy
strcpy:
    # rdi: dst
    # rsi: src

    .loop:
        movb (%rdi), %al
        movb %al,    (%rsi)

        inc  %rdi
        inc  %rsi

        test %al,    %al
        jnz  .loop

    ret
