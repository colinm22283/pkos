.code32

.section .bootloader, "a"

.global print_hex
print_hex:
    movl (console_ptr), %ebx
    xor  %ecx,          %ecx
    mov  $hex_lut,      %edx

    mov  %al,             %cl
    and  $0x0F,           %cl
    movb (%edx, %ecx, 1), %cl
    movb %cl,             6(%ebx)
    shr  $4,              %eax

    mov  %al,             %cl
    and  $0x0F,           %cl
    movb (%edx, %ecx, 1), %cl
    movb %cl,             4(%ebx)
    shr  $4,              %eax

    mov  %al,             %cl
    and  $0x0F,           %cl
    movb (%edx, %ecx, 1), %cl
    movb %cl,             2(%ebx)
    shr  $4,              %eax

    mov  %al,             %cl
    and  $0x0F,           %cl
    movb (%edx, %ecx, 1), %cl
    movb %cl,             (%ebx)

    add $8, %ebx
    movl %ebx, (console_ptr)

    ret

hex_lut: .string "0123456789ABCDEF"
