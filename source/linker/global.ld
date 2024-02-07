SECTIONS {
    . = 0x80000 - 0x1000;
    .memory_map (NOLOAD) : {
        *(.memory_map);
    } > usable_memory_2

    . = 0x80000 - 0x1000 - 4;
    .memory_map_length (NOLOAD) : {
        *(.memory_map_size);
    } > usable_memory_2
}