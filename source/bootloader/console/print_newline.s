.code32

.section .bootloader, "a"

.global print_newline
print_newline:
    movl (newline_ptr), %eax
    movl %eax,          (console_ptr)
    add  $80,           %eax
    movl %eax,          (newline_ptr)

    ret
