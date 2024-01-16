.code32

.section .bootloader, "a"

CONSOLE_WIDTH  = 40
CONSOLE_HEIGHT = 25

.global boot_error
boot_error:
    # clear the screen
    mov $0xB8000,                            %ebx
    mov $(CONSOLE_HEIGHT * CONSOLE_WIDTH), %ecx
    .clear_loop:
        movw $0x1F00,       (%ebx)
        add  $2,          %ebx
        loop .clear_loop

    # reset console pointer
    movl $0xB8000, (console_ptr)
    movl $(0xB8000 + 80), (newline_ptr)

    mov %eax, %edi

    mov  $error_string_1, %eax
    call print_string

    mov  %edi, %eax
    call print_hex

    call print_newline
    call print_newline

    mov $error_table, %ebx
    mov (%ebx, %edi, 4), %eax
    call print_string

    hlt

error_string_1: .asciz "BOOT ERROR 0x"

error_table:
    .long cpuid_not_supported
    .long extended_cpuid_not_supported
    .long long_mode_not_supported

cpuid_not_supported: .asciz "CPUID FUNCTIONS ARE NOT SUPPORTED"
extended_cpuid_not_supported: .asciz "EXTENDED CPUID FUNCTIONS ARE NOT SUPPORTED"
long_mode_not_supported: .asciz "LONG MODE IS NOT SUPPORTED BY THE CPU"
