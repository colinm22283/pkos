OUTPUT_FORMAT("binary");
ENTRY(kernel_entry);
SECTIONS {
    . = _kernel_entry;

    .kernel : AT(0x0000) {
        *(.kernel_entry*);
        *(.text*);
        *(.rodata*);
        *(.data*);
        *(.bss*);
    }
}