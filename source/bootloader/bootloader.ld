OUTPUT_FORMAT("binary");
ENTRY(protected_mode_entry);
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
        *(.bootloader);
        *(.gdt64);
        *(.gdt64_ptr);
    } > usable_memory_2

    .page_tables : {
        . = ALIGN(4096);
        *(.page_tables);
    } > usable_memory_2
}