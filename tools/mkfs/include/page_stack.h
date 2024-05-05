#pragma once

#include <filesystem.h>

extern filesystem_root_page_t root_page;
extern filesystem_node_page_t * pages;
extern uint64_t page_count;
extern uint64_t page_capacity;

void page_stack_init();
void page_stack_free();

filesystem_page_address_t add_fs_page(filesystem_node_page_t * page);
filesystem_page_address_t add_dir_index_entry(filesystem_page_address_t index_address, filesystem_node_page_t * page);