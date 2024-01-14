OUTPUT_FORMAT("binary");
ENTRY(_bootloader32_entry);
SECTIONS {
    . = 0x1000;

    . = ALIGN(0x1000);
    _kernel_stack_base = .;
    . = 0x7BFF;
    . = ALIGN(64);
    _kernel_stack_top = .;

    . = 0x7C00;

    _bootloader32_entry = .;

    . += 0x200; /* space for the bootloader32 */

    _bootloader64_entry = .;

    . += 0x400; /* space for the bootloader64 */

    _kernel_entry_lower = .;

    _kernel_paging_tables_base_lower = .;
    kernel_pml4t_lower = .;
    . += 0x1000;
    kernel_pdpt_lower = .;
    . += 0x1000;
    kernel_pdt_lower = .;
    . += 0x1000;
    kernel_pt1_lower = .;
    . += 0x1000;
    _kernel_paging_tables_top_lower = .;
    _kernel_paging_tables_size_lower = _kernel_paging_tables_top_lower - _kernel_paging_tables_base_lower;

    /* up here is normally where the kenrel wil reside */

    . = 0xC0000000;

    _kernel_entry = .;

    . += 0xC0000000 + 0x200000 - 0x4000;

    _kernel_paging_tables_base = .;
    kernel_pml4t = .;
    . += 0x1000;
    kernel_pdpt = .;
    . += 0x1000;
    kernel_pdt = .;
    . += 0x1000;
    kernel_pt1 = .;
    . += 0x1000;
    _kernel_paging_tables_top = .;
    _kernel_paging_tables_size = _kernel_paging_tables_top - _kernel_paging_tables_base;
}