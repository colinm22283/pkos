.code32

.section .bootloader64_text, "a"
.global _bootloader64_entry
.type _bootloader64_entry, @function
_bootloader64_entry:
    # check if long mode is available
    mov $0x80000000, %eax
    cpuid
    cmp $0x80000001, %eax
    mov $0x0001, %ax
    jb .boot_error

    mov $0x80000001, %eax
    cpuid
    test $(1 << 29), %edx
    mov $0x0002, %ax
    jz .boot_error

    mov $1, %eax
    cpuid
    test $(1 << 8), %edx
    mov $0x0003, %ax
    jz .boot_error

    # load the tss address into the gdt
    mov  $(gdt64 + 0x30 + 16), %eax
    mov  $tss64, %ebx
    movw %bx, (%eax)
    add  $16, %eax
    shr  $16, %ebx
    movb %bl, (%eax)
    add  $16, %eax
    movb %bh, (%eax)

    # enable paging and identity map the first 2 MB
    # set the pdpt address
    mov  $_kernel_paging_tables_base_lower, %eax
    mov  %eax,                 %cr3
    # clear the table memory
    mov  $_kernel_paging_tables_base_lower, %eax
    .clear_loop:
        movb $0,                  (%eax)
        add  $1,                  %eax
        cmp  $_kernel_paging_tables_top_lower, %eax
        jb   .clear_loop
    # load the tables
    mov  $_kernel_paging_tables_base_lower,            %eax
    movl $(_kernel_paging_tables_base_lower + 0x1003), (%eax)
    add  $0x1000,                         %eax
    movl $(_kernel_paging_tables_base_lower + 0x2003), (%eax)
    add  $0x1000,                         %eax
    movl $(_kernel_paging_tables_base_lower + 0x3003), (%eax)
    add  $0x1000,                         %eax
    # identity map until 2 MB
    mov $0x00000003, %ebx
    mov $512, %ecx
    .id_map_loop:
        movl %ebx,    (%eax)
        add  $0x1000, %ebx
        add  $8,      %eax
        sub  $1,      %ecx
        loop .id_map_loop
    # identity map the first 2 MB with the stack
    # clear the allocated memory
    #                                 THIS USES THE BOTTOM 0x3000 BYTES OF THE STACK DO NOT OVERWRITE!!!
    #mov $0x2000, %esp
    mov $0x3000, %ecx
    mov $_kernel_stack_base, %eax
    .stack_table_clear_loop:
        movb $0,  (%eax)
        inc  %eax
        loop .stack_table_clear_loop
    # write the page tables
    mov $_kernel_stack_base, %eax
    movl $(_kernel_stack_base + 0x1003), (%eax)
    add $0x1000, %eax
    movl $(_kernel_stack_base + 0x2003), (%eax)
    add $0x1000, %eax
    mov $0x00000003, %ebx
    mov $512, %ecx
    .lid_map_loop:
        movl %ebx,    (%eax)
        add  $0x1000, %ebx
        add  $8,      %eax
        sub  $1,      %ecx
        loop .lid_map_loop
    # set the pml4t to point to our sturcture
    movl $(_kernel_stack_base + 0x3), (kernel_pml4t_lower)

    # enable PAE flag
    mov %cr4,      %eax
    or  $(1 << 5), %eax
    mov %eax,      %cr4

    # enter long mode 32 bit compatibility mode
    mov   $0xC0000080, %ecx
    rdmsr
    or    $(1 << 8),   %eax
    wrmsr

    # enable paging
    mov %cr0,        %eax
    or  $0x80000000, %eax
    mov %eax,        %cr0

    lgdt gdt64_descriptor
    jmp $0x10, $_long_mode_entry

    .boot_error:
        mov $0xB8000, %ecx
        mov $..boot_error_string, %ebx
        jmp ..print_loop
        ..boot_error_string: .byte 'B', 'O', 'O', 'T', ' ', 'E', 'R', 'R', 'O', 'R', ':', ' ', '0', 'x'
        ..print_loop:
            movb (%ebx),    %dl
            movb %dl,       (%ecx)

            add  $1,        %ebx
            add  $2,        %ecx

            cmp  $0xB801C, %ecx
            jl  ..print_loop

        mov $0xB8022, %ebx
        mov $4,       %ecx
        ..hex_loop:
            xor %edx, %edx
            mov %al,  %dl
            and $0xF, %dl
            add $.hex_lut, %edx
            movb (%edx), %dl
            movb %dl, (%ebx)

            sub $2, %ebx
            shr $4, %ax

            loop ..hex_loop

        mov $0xB8001,   %eax
        ..clear_loop:
            movb $0x1F, (%eax)
            add  $2,  %eax

            cmp $(0xB8000 + (2 * 40 * 25)), %eax
            jb  ..clear_loop

        jmp .halt

    .hex_lut: .string "0123456789ABCDEF"

    .halt:
        hlt
        jmp .halt

.code64
_long_mode_entry:
    cli
    mov $0x20, %ax
    mov %ax,   %ds
    mov %ax,   %es
    mov %ax,   %fs
    mov %ax,   %gs
    mov %ax,   %ss

    # load the tss
    mov $0x30, %ax
    ltr %ax

    jmp _kernel_entry_lower
