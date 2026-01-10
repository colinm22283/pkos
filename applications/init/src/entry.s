.code64

OPEN  = 0
CLOSE = 1
WRITE = 2
READ  = 3
SEEK  = 4
EXIT  = 5

.section .start
.global _start
_start:
    mov  %rsp, %rbp

    call main

    mov %rax,  %rbx
    mov $EXIT, %rax
    int $0x30

.global program
program:
    mov $8, %rax
    int $0x30

    cmp $0, %rax
    je parent
    child:


        mov $5, %rax
        int $0x30
    parent:
        mov $5, %rax
        int $0x30

    ret
