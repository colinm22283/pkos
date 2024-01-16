.code32

.section .bootloader, "a"
.global print_string
print_string:
    movl (console_ptr), %ebx
    movb (%eax), %cl
    .print_loop:
        movb %cl,    (%ebx)
        inc  %eax
        add  $2,     %ebx
        movb (%eax), %cl
        test %cl,    %cl
        jnz  .print_loop

    movl %ebx, (console_ptr)

    ret

.section .bootloader, "a"
.global print_string_nl
print_string_nl:
    call print_string
    call print_newline

    ret
