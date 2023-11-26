OUTPUT_FORMAT("binary");
ENTRY(_start);
SECTIONS {
    . = 0x0500;

    .bootloader_stack : {
        . = ALIGN(16);
        *(.stack*);
    }

    . = 0x7C00;

    .bootloader : AT(0x0000) {
        *(.bootloader_text);
        *(.bootloader_rodata);
        *(.bootloader_gdt);
        *(.bootloader_gdt_descriptor);
    }

    .sig 0x7DFE : AT(0x01FE) {
        SHORT(0xAA55);
    }

    . = 0x7E00;

    .text : AT(0x0200) {
        *(.text*);
        *(.rodata*);
    }
}