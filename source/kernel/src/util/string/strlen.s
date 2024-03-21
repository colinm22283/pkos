.code64

.global strlen
strlen:
    # edi: string

    xor  %eax,   %eax

    movb (%edi), %cl

    .loop:
        test %cl,    %cl
        jz   .return

        inc  %eax
        inc  %edi

        movb (%edi), %cl
        jmp  .loop

.return:
    ret
