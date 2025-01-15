#include <entry.h>

#include <sys/halt.h>

#include <driver/disc_pio.h>

#include <memory/primary_region.h>

#include <paging/init.h>
#include <paging/bitmap.h>
#include <paging/temp_page.h>

#include <util/memory/memset.h>

#include <stack.h>

#include <sys/stack/load_stack_pointer.h>

#include <entry_error.h>

__NORETURN __SECTION(".kernel_entry") void kernel_entry() {
    load_stack_pointer(stack_top);

    primary_region_init();

    driver_disc_pio_load(&driver_table);
    if (!driver_table.disc.start()) kernel_entry_error(0x1);

    paging_init();

//    int_init();

//    uint16_t device_count = driver_table.disc.device_count();
    driver_table.disc.select_device(0);

//    hlt();

#define VIDEO_MEMORY ((uint8_t *) 0xA0000000)

    uint64_t pt_addr = bitmap_reserve_level(1);
    uint64_t pdt_addr = bitmap_reserve_level(0);

    {
        temp_pt_map_page(pt_addr);
        pt64_t * pt = PAGING_TEMP_PT_VADDR;
        memset(pt, 0, sizeof(pt64_t));

        pt64_entry_t * pt_entry = pt64_map_address(pt, 0xA0000, VIDEO_MEMORY);
        pt_entry->present = true;
        pt_entry->read_write = true;
    }

    {
        temp_pt_map_page(pdt_addr);
        pdt64_t * pdt = PAGING_TEMP_PT_VADDR;
        memset(pdt, 0, sizeof(pdt64_t));

        pdt64_entry_t * pdt_entry = pdt64_map_address(pdt, pt_addr, VIDEO_MEMORY);
        pdt_entry->present = true;
        pdt_entry->read_write = true;
    }

    {
        pdpt64_entry_t * pdpt_entry = pdpt64_map_address(&paging_kernel_pdpt, pdt_addr, VIDEO_MEMORY);
        pdpt_entry->present = true;
        pdpt_entry->read_write = true;
    }

    VIDEO_MEMORY[0] = 3;
    VIDEO_MEMORY[1] = 3;
    VIDEO_MEMORY[2] = 3;

    bitmap_free_level(1, pt_addr);
    bitmap_free_level(0, pdt_addr);

    uint64_t ori_pt = pt_addr;
    uint64_t ori_pdt = pdt_addr;

    pt_addr = bitmap_reserve_level(1);
    pdt_addr = bitmap_reserve_level(0);

    asm volatile ("mov %0, %%r8\nmov %1, %%r9\nmov %2, %%r10\nmov %3, %%r11\nhlt" : : "r" (pt_addr), "r" (pdt_addr), "r" (ori_pt), "r" (ori_pdt));

//    module_info_table_t * hello_world_entry_table = module_load(open_filesystem(FILESYSTEM_ROOT_ADDRESS), "boot/module/hello_world.mod");

//    hello_world_entry_table->init(hello_world_entry_table);

    driver_table.disc.stop();

    halt();
}
