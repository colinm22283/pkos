OUTPUT_FORMAT("binary");
ENTRY(_bootloader64_entry);
SECTIONS {
    . = 0x7E00;

    .bootloader64 : AT(0x0000) {
        *(.bootloader64_text);

    }
    .bootloader64_gdt : {
        *(.bootloader64_gdt);
    }
    .bootloader64_gdt_descriptor : {
        *(.bootloader64_gdt_descriptor);
    }
    .bootloader64_tss : {
        *(.bootloader64_tss);
    }
}