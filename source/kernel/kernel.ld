OUTPUT_FORMAT("binary");
ENTRY(bootloader16_entry);
SECTIONS {
    . = 0x100000;
    .kernel_entry : AT(0) {
        *(.kernel_entry);
    } > kernel_memory

    .text : {
        *(.text);
        *(.data);
    } > kernel_memory
}