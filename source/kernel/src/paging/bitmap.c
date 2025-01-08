#include <stdint.h>

#include <paging/bitmap.h>
#include <paging/region.h>
#include <paging/tables.h>
#include <paging/translation.h>
#include <paging/temp_page.h>

#include <util/memory/memset.h>
#include <util/math/div_up.h>
#include <util/math/min.h>

uint64_t bitmap_available_pages;
uint64_t bitmap_size;
uint64_t bitmap_paddr;

void paging_bitmap_init(void) {
    pml4t64_entry_t * bitmap_pml4t_entry = pml4t64_map_address(
        &paging_kernel_pml4t,
        paging_kernel_virtual_to_physical(paging_bitmap_pdpt),
        PAGING_BITMAP_VADDR
    );
    bitmap_pml4t_entry->present = true;
    bitmap_pml4t_entry->read_write = true;

    memset(paging_temp_pt, 0, sizeof(pt64_t));

    uint64_t paging_region_size = paging_region_end - paging_region_start;

    uint64_t bitmap_overestimate = 0;
    for (uint64_t i = 0; i < PAGING_BITMAP_LEVELS; i++) bitmap_overestimate += DIV_UP(paging_region_size, (0x1000 * 8 * (i + 1)));

    uint64_t pt_region_overestimate = DIV_UP(bitmap_overestimate, 0x1000 * 512) * 0x1000;
    uint64_t pdt_region_overestimate = DIV_UP(bitmap_overestimate, 0x1000 * 512 * 512) * 0x1000;

    uint64_t remaining_space = paging_region_size - pt_region_overestimate - pdt_region_overestimate;

    const uint64_t multiplier = 0x1000 * 8 * PAGING_BITMAP_LEVELS;
    uint64_t msum = 0;
    for (uint64_t i = 0; i < PAGING_BITMAP_LEVELS; i++) msum += multiplier / (0x1000 * 8 * (i + 1));

    uint64_t available_space = (remaining_space * multiplier) / (multiplier + msum);
    bitmap_size = (available_space * msum) / (multiplier);
    bitmap_available_pages = available_space / 0x1000;

    const uint64_t pt_count = DIV_UP(bitmap_size, 0x1000 * 512);
    const uint64_t pdt_count = DIV_UP(bitmap_size, 0x1000 * 512 * 512);

    bitmap_paddr = paging_region_start + 0x1000 * (pt_count + pdt_count);

    {
        uint64_t pt_paddr = paging_region_start;

        for (uint64_t i = 0; i < pt_count; i++) {
            temp_pt_map_page(pt_paddr);

            pt64_t * pt = PAGING_TEMP_PT_VADDR;
            memset(pt, 0, sizeof(pt64_t));

            pt64_map_2mb(pt, bitmap_paddr);

            bitmap_paddr += 0x1000 * 512;

            pt_paddr += sizeof(pt64_t);
        }
    }

    {
        uint64_t pt_paddr = paging_region_start;
        uint64_t pdt_paddr = paging_region_start + 0x1000 * pt_count;

        char * vaddr = (char *) PAGING_BITMAP_VADDR;

        uint64_t pt_remaining = pt_count;
        for (uint64_t i = 0; i < pdt_count; i++) {
            temp_pt_map_page(pdt_paddr);

            pdt64_t * pdt = PAGING_TEMP_PT_VADDR;
            memset(pdt, 0, sizeof(pdt64_t));

            for (uint64_t j = 0; j < MIN(512, pt_remaining); j++) {
                pdt64_entry_t * pdt_entry = pdt64_map_address(pdt, pt_paddr, vaddr);
                pdt_entry->present = true;
                pdt_entry->read_write = true;

                vaddr += 0x1000 * 512;
                pt_paddr += sizeof(pt64_t);
                pt_remaining--;
            }

            pdt_paddr += sizeof(pdt64_t);
        }
    }

    {
        uint64_t pdt_paddr = paging_region_start + 0x1000 * pt_count;

        char * vaddr = (char *) PAGING_BITMAP_VADDR;

        for (uint64_t i = 0; i < pdt_count; i++) {
            pdpt64_entry_t * pdpt_entry = pdpt64_map_address(&paging_bitmap_pdpt, pdt_paddr, vaddr);
            pdpt_entry->present = true;
            pdpt_entry->read_write = true;

            vaddr += 0x1000 * 512 * 512;
            pdt_paddr += sizeof(pdt64_t);
        }
    }

    memset(PAGING_BITMAP_VADDR, 0, bitmap_size);
}