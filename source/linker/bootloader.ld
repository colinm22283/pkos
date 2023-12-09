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
        *(.bootloader_gdt64);
        *(.bootloader_gdt64_descriptor);
    }

    .sig 0x7DFE : AT(0x01FE) {
        SHORT(0xAA55);
    }

    . = 0x7E00;

    .bootloader32 : AT(0x0200) {
        *(.bootloader32_text);
        *(.bootloader32_rodata);
    }

    . = ALIGN(512);

    _bootloader_sectors = (. - 0x200) / 512;

    .paging_tables : {
        _page_table_base = .;
        . += 500;
        _page_table_top = .;
    }

    .text : {
        *(.text*);
        *(.rodata*);
        *(.data*);
    }

    .heap 0x8800 : {
        _heap_base = .;
        . += 0x5000;
        _heap_top = .;
        _heap_size = _heap_top - _heap_base;
    }
}