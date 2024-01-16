.code16

.section .boot_sector, "a"
.global bootloader16_entry
bootloader16_entry:
    # disable interrupts
    cli

    # set a stack pointer
    mov $stack_top, %sp

    # set console graphics mode
	mov $0x0001, %ax
	int $0x10

    # disable the cursor
	mov $0x01,   %ah
	mov $0x2000, %cx
	int $0x10

    # check for extended bios functions
    mov $0x41,   %ah
    mov $0x55AA, %bx
    mov $0x80,   %dl
    int $0x13
    jc  bios_extensions_not_found

    # load the rest of the bootloader into memory
    mov $(0x0200 | 7), %ax # number of sectors
    mov $0x7E00, %bx
    mov $0x0002, %cx
    mov $0x0080, %dx
    int $0x13
    jc  bootloader_load_error

    # enable A20 line
    stc
    mov $0x2401, %ax
    int $0x15
    jc  a20_failure

    # load the gdt
    lgdt gdt32_ptr

    # enable the gdt
    mov %cr0, %eax
    or  $1, %al
    mov %eax, %cr0

    # enter the protected mode portion of the kernel
    ljmp $0x08, $protected_mode_entry

bios_extensions_not_found:
    mov $25, %cx
    mov $bios_extensions_not_found_str, %bp
    jmp bl16_print_error_string
bootloader_load_error:
    mov $21, %cx
    mov $bootloader_load_error_str, %bp
    jmp bl16_print_error_string
a20_failure:
    mov $22, %cx
    mov $a20_failure_str, %bp
bl16_print_error_string:
    mov $0x1300, %ax
    mov $0x004F, %bx
    xor %dx, %dx
    int $0x10
    hlt

bios_extensions_not_found_str: .string "BIOS EXTENSIONS NOT FOUND"
bootloader_load_error_str: .string "BOOTLOADER LOAD ERROR"
a20_failure_str: .string "A20 LINE ENABLE FAILED"

