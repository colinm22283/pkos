.code32

.global console_print_bool
console_print_bool:
    movb 8(%esp), %al

    test %al, %al
    jz   .false
    .true:
        push $true_string

        jmp  .end
    .false:
        push $false_string

    .end:
        call console_print
        add  $4, %esp
        ret

true_string: .asciz "true"
false_string: .asciz "false"