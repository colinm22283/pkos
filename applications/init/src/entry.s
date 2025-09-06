.code64

OPEN  = 0
CLOSE = 1
WRITE = 2
READ  = 3
SEEK  = 4
EXIT  = 5

.section .rodata
test_string: .string "HELLO WORLD\n"

.section .start
.global _start
_start:
    mov  %rsp, %rbp

    call main

exit:

    mov %rax,  %rbx
    mov $EXIT, %rax
    int $0x30
