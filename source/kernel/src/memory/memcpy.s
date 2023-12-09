.code32

.global memcpy
.type memcpy, @function
memcpy:
    push %ebp
    mov  %esp, %ebp
    push %ebx

    movl 8(%ebp),  %edx # dest
    movl 12(%ebp), %ecx # src
    movl 16(%ebp), %eax # size

    .loop:
        cmp  $0,     %eax
        je   .exit

        movb (%ecx), %bl
        movb %bl,    (%edx)

        sub  $1,     %eax
        add  $1,     %ecx
        add  $1,     %edx

        jmp  .loop
    .exit:

    pop %ebx
    pop %ebp
    ret
