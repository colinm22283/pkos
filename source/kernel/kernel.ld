OUTPUT_FORMAT("binary");
ENTRY(kernel_entry);
SECTIONS {
    . = 0xC0000000;

    .kernel_entry . : AT(0) {
        *(.kernel_entry);
    } > kernel_memory

    .text . : {
        *(.text*);
        *(.data*);
        *(.rodata*);
    } > kernel_memory

    .bss . (NOLOAD) : {
        *(.bss*);
    } > kernel_memory

    .stack . (NOLOAD) : {
        _stack_base = .;
        . += 1024;
        . = ALIGN(8);
        _stack_top = .;
    } > kernel_memory

    .allocation_space . (NOLOAD) : {
        *(.allocation_space);
    }

    .filesystem . : AT(0x10000) {
        *(.filesystem);
    } > kernel_memory
}