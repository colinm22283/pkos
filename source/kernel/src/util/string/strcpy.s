.code64

.global strcpy
strcpy:
    # rdi: dst
    # rsi: src

    movb (%rdi), %al
    test %al,    %al
    jz   .return

    .loop:
        movb %al, (%rsi)

        inc  %rdi
        inc  %rsi

        movb (%rdi), %al
        test %al,    %al
        jnz  .loop

.return:
    ret
