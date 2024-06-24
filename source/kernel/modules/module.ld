OUTPUT_FORMAT("binary");
ENTRY(kernel_entry);
SECTIONS {
    . = 0;

    .text . : AT(0) {
        *(.entry_table);
        *(.text*);
        *(.rodata*);
    }
}