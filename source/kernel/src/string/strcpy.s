.code32

.section .text
.global strcpy
.type strcpy, @function
strcpy:
    push %ebp
    mov %esp, %ebp

    movl 8(%ebp), %ecx
    movl 12(%ebp), %edx

    .loop:
        movb (%edx), %al
        movb %al,   (%ecx)

        add  $1,    %ecx
        add  $1,    %edx

        cmp  $0,     %al
        jne  .loop

    pop %ebp
    ret
