OUTPUT_FORMAT("binary");
ENTRY(kernel_entry);
SECTIONS {
    . = 0;

    .text . : AT(0) {
        _entry_table_start = .;
        *(.entry_table);
        _entry_table_end = .;
        *(.text*);
    }

    .zero_size . : {
        _zero_size_start = .;
        *(.rodata*);
        *(.bss*);
        _zero_size_end = .;
    }

    ASSERT(_zero_size_end == _zero_size_start, "Module must not have a rodata or bss section")
    ASSERT(_entry_table_start != _entry_table_end, "Module must contain an entry table")
}