OUTPUT_FORMAT("binary");
ENTRY(kernel_entry);
SECTIONS {
    . = 0xC0000000;

    _kernel_start = .;

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
        . += 4096;
        . = ALIGN(8);
        _stack_top = .;
    } > kernel_memory

    _kernel_end = .;

    _kernel_size = _kernel_end - _kernel_start;

    . = ALIGN(0x1000);

    .allocation_space . (NOLOAD) : {
        _allocation_space_start = .;
        *(.allocation_space);
        _allocation_space_end = .;

        _allocation_space_size = _allocation_space_end - _allocation_space_start;
    }
}
