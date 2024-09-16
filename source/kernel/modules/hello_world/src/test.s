.code64

.global test_func
test_func:
    mov %rdi, %rax

    .loop:
        hlt
        jmp .loop
