.code16

.section .stack
    .align 16
    _stack_bottom:
    .skip 0x76FF
    _stack_top:

.section .bootloader_rodata, "a"


.section .bootloader_text, "a"
    .global _start
    .type _start, @function
_start:
    # disable interrupts
    cli

    # enable A20 line
    mov $0x2401, %ax
    int $0x15

    # set console graphics mode
    xor %ah, %ah
	mov $0x01, %al
	int $0x10

    # load kernel memory
    mov $0x02, %ah
    mov $0x01, %al # number of sectors
    mov $0x0002, %cx
    xor %dh, %dh
    xor %bx, %bx
    mov %bx, %es
    mov $0x7E00, %bx
    int $0x13

    # load the gdt
    lgdt [gdt_descriptor]
    mov %cr0, %eax
    or  $1, %al
    mov %eax, %cr0

    jmp $0x08, $protected_mode_entry

.code32
protected_mode_entry:
    # set the segment registers
    mov $0x10, %ax
    mov %ax, %ds
    mov %ax, %es
    mov %ax, %fs
    mov %ax, %gs
    mov %ax, %ss

    # set the stack pointer
    mov $_stack_top, %esp

    # enter the kernel
	jmp _kernel_entry
