OUTPUT_FORMAT("binary");
ENTRY(bootloader_entry);
SECTIONS {
    . = 0x0500;
    .stack (NOLOAD) : {
        stack_base = .;
        . += 0x07C00 - 0x00500 - 8;
        . = ALIGN(8);
        stack_top = .;
    } > usable_memory_1

    . = 0x7E00;

    .bootloader : AT(0x0000) {
        *(.bootloader_entry);
        *(.text*);
        *(.rodata*);
    } > usable_memory_2

    . = 0x9E00;

    .bootloader_bss (NOLOAD) : {
        *(.bss*);
        *(.gdt64);
        *(.gdt64_ptr);
        *(.page_tables);
    }
}