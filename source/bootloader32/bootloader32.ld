OUTPUT_FORMAT("binary");
ENTRY(_bootloader32_entry);
SECTIONS {
    . = _bootloader32_entry;

    .bootloader32 : AT(0x0000) {
        *(.bootloader32_text);
        *(.bootloader32_rodata);
        *(.bootloader32_gdt);
        *(.bootloader32_gdt_descriptor);
    }

    .sig 0x7DFE : AT(0x01FE) {
        SHORT(0xAA55);
    }
}