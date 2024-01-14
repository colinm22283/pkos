.code16

#.section .stack
#    .align 16
#    _kernel_stack_bottom:
#    .skip 0x71FF
#    .align 16
#    _kernel_stack_top:

.section .bootloader32_text, "a"
.global _bootloader32_entry
.type _bootloader32_entry @function
_bootloader32_entry:
    # disable interrupts
    cli

    # set a stack pointer
    mov $_kernel_stack_top, %sp

    # check for extended bios functions
    mov $0x41,   %ah
    mov $0x55AA, %bx
    mov $0x80,   %dl
    int $0x13
    jc  bios_extensions_not_found

    # enable A20 line
    mov $0x2401, %ax
    int $0x15

    # set console graphics mode
	mov $0x0001, %ax
	int $0x10

    # load the bootloader64 and kernel into memory
    mov $(0x0200 | 127), %ax # number of sectors
    mov $0x7E00, %bx
    mov $0x0002, %cx
    mov $0x80, %dx
    int $0x13
    jc  read_failed

    # load the gdt
    lgdt gdt32_descriptor
    mov %cr0, %eax
    or  $1, %al
    mov %eax, %cr0

    jmp $0x08, $_protected_mode_entry

read_failed:
    mov $17,   %cx
    mov $.read_failed_str, %bp
    jmp print_error
    .read_failed_str: .string "SECTOR READ ERROR"
bios_extensions_not_found:
    mov $25,   %cx
    mov $.bios_extensions_not_found_str, %bp
    jmp print_error
    .bios_extensions_not_found_str: .string "BIOS EXTENSIONS NOT FOUND"
print_error:
    mov $0x1300, %ax
    mov $0x00F4, %bx
    xor %dx,     %dx
    int $0x10
    cli
    hlt

.code32
_protected_mode_entry:
    # set the segment registers
    mov $0x10, %ax
    mov %ax, %ds
    mov %ax, %es
    mov %ax, %fs
    mov %ax, %gs
    mov %ax, %ss

    # set the kernel stack pointer
    mov $_kernel_stack_top, %esp

    # enter the next bootloader stage
    jmp _bootloader64_entry
