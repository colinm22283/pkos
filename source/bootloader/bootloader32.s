.code32

.section .bootloader, "a"
.global protected_mode_entry
protected_mode_entry:
    # set the segment registers
    mov $0x10, %ax
    mov %ax,   %ds
    mov %ax,   %es
    mov %ax,   %fs
    mov %ax,   %gs
    mov %ax,   %ss

    # set the stack pointer
    mov $stack_top, %esp

    # print the pkbootloader string
    mov  $title_string, %eax
    call print_string_nl
    call print_newline

    # check for cpuid support
    pushfl
    popl   %ebx
    mov    %ebx, %ecx
    xor    $(1 << 21), %ebx
    pushl  %ebx
    popfl
    pushfl
    popl   %ebx
    pushl  %ecx
    popfl
    xor    %ecx, %ebx
    mov $0x0000, %eax
    jz     boot_error

    # check for extended function support
    mov $0x80000000, %eax
    cpuid
    cmp $0x80000001, %eax
    mov $0x0001, %eax
    jb boot_error

    # check for long mode support
    mov $0x80000001, %eax
    cpuid
    test $(1 << 29), %edx
    mov $0x0002, %ax
    jz boot_error

    # print page table allocation message
    mov $page_table_alloc_string, %eax
    call print_string_nl



    hlt

title_string: .asciz "PKOS Bootloader V1 Booting..."
page_table_alloc_string: .asciz "Allocating page tables..."
