.code32

.section .bootloader32_text, "a"
.global _bootloader32_entry
.type _bootloader32_entry, @function
_bootloader32_entry:
    # check if long mode is available
    mov $0x80000000, %eax
    cpuid
    cmp $0x80000001, %eax
    jb .long_mode_not_available

    mov $0x80000001, %eax
    cpuid
    test $(1 << 29), %edx
    jz .long_mode_not_available

    jmp .long_mode_available
    .long_mode_not_available:
        mov $0x0001, %ax
        jmp .boot_error
    .long_mode_available:

    # enable paging
    call _paging_init




    mov $0xABCD, %ax
    jmp .boot_error





    .boot_error:
        movw $('B' | 0x1F00), (0xB8000)
        movw $('E' | 0x1F00), (0xB8002)
        movw $(':' | 0x1F00), (0xB8004)
        movw $(' ' | 0x1F00), (0xB8006)
        movw $('0' | 0x1F00), (0xB8008)
        movw $('x' | 0x1F00), (0xB800A)

        movl $0x1F001F00,     (0xB800C)
        movl $0x1F001F00,     (0xB8010)

        xor  %ebx,      %ebx
        mov  %al,       %bl
        and  $0x0F,     %bl
        add  $.hex_lut, %ebx
        movb (%ebx),    %bl
        movb %bl,       (0xB8012)

        xor  %ebx,      %ebx
        mov  %al,       %bl
        and  $0xF0,     %bl
        shr  $4,        %bl
        add  $.hex_lut, %ebx
        movb (%ebx),    %bl
        movb %bl,       (0xB8010)

        xor  %ebx,      %ebx
        mov  %ah,       %bl
        and  $0x0F,     %bl
        add  $.hex_lut, %ebx
        movb (%ebx),    %bl
        movb %bl,       (0xB800E)

        xor  %ebx,      %ebx
        mov  %ah,       %bl
        and  $0xF0,     %bl
        shr  $4,        %bl
        add  $.hex_lut, %ebx
        movb (%ebx),    %bl
        movb %bl,       (0xB800C)

        mov $0xB8013,   %eax
        ..clear_loop:
            movb $0x1F, (%eax)
            add  $2,  %eax

            cmp $(0xB8000 + (2 * 40 * 25)), %eax
            jb  ..clear_loop

        jmp .halt

    .hex_lut: .byte '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'

    .halt:
        jmp .halt
