#include <entry.h>

#include <sys/halt.h>

#include <driver/disc_pio.h>
#include <driver/video_bios.h>

#include <paging/map_kernel.h>

#include <stack.h>

#include <sys/stack/load_stack_pointer.h>

#include <filesystem/init.h>
#include <filesystem/get_root_directory.h>
#include <filesystem/directory_locate_directory.h>
#include <filesystem/directory_iterator.h>

#include <util/string/strcpy.h>

typedef struct { int32_t x; int32_t y; } point_t;

__NORETURN __SECTION(".kernel_entry") void kernel_entry() {
    load_stack_pointer(stack_top);

    paging_map_kernel();

    driver_disc_pio_load(&driver_table);
    driver_table.disc.start();

    driver_video_bios_load(&driver_table);
    driver_table.video.start();

    uint16_t device_count = driver_table.disc.device_count();
    driver_table.disc.select_device(0);

    driver_table_video_mode_t * video_modes = driver_table.video.get_modes();
    uint32_t video_modes_count = driver_table.video.mode_count();
    driver_table.video.set_mode(0);

    char * console_ptr = (char *) 0xB8000;

    for (int i = 0; i < 80 * 25; i++) {
        ((char *) 0xB8000)[i * 2] = ' ';
    }

    filesystem_t filesystem;
     filesystem_init(&filesystem, 0x13200 / 512);

    filesystem_directory_page_t root_dir;
    get_root_directory(&filesystem, &root_dir);

    filesystem_directory_page_t home_dir;
    filesystem_directory_locate_directory(&root_dir, "home", &home_dir);

    filesystem_directory_iterator_t home_iterator;
    filesystem_directory_iterator_generate(&home_dir, &home_iterator);
    do {
        filesystem_directory_page_t directory;
        if (!filesystem_directory_iterator_get(&home_iterator, &directory)) break;

        for (int i = 0; directory.name[i] != '\0'; i++) {
            *console_ptr = directory.name[i];

            console_ptr += 2;
        }
        *console_ptr = ' ';
        console_ptr += 2;
    }
    while (filesystem_directory_iterator_next(&home_iterator));

    driver_table.disc.stop();
    driver_table.video.stop();

    halt();
}

__SECTION(".filesystem") struct {
    filesystem_root_page_t root_page;
    filesystem_directory_page_t root_directory;
    filesystem_directory_index_page_t root_index;
    filesystem_directory_page_t directory_1;
    filesystem_directory_index_page_t directory_1_index;
    filesystem_directory_page_t directory_11;
    filesystem_directory_page_t directory_12;
} filesystem = {
    .root_page = {
        .signature = FILESYSTEM_ROOT_SIGNATURE,
        .root_directory_index_address = 0x13200 / 512 + 1,
    },
    .root_directory = {
        .signature = FILESYSTEM_SIGNATURE_DIRECTORY,
        .parent_directory_address = 0,
        .name = "TEST FILESYSTEM",
        .index_address = 0x13200 / 512 + 2,
    },
    .root_index = {
        .parent_directory_address = 0x13200 / 512 + 1,
        .next = 0,
        .children = {
            0x13200 / 512 + 3,
            0,
        },
    },
    .directory_1 = {
        .signature = FILESYSTEM_SIGNATURE_DIRECTORY,
        .name = "home",
        .parent_directory_address = 0x13200 / 512 + 1,
        .index_address = 0x13200 / 512 + 4,
    },
    .directory_1_index = {
        .parent_directory_address = 0x13200 / 512 + 3,
        .next = 0,
        .children = {
            0x13200 / 512 + 5,
            0x13200 / 512 + 6,
            0,
        },
    },
    .directory_11 = {
        .signature = FILESYSTEM_SIGNATURE_DIRECTORY,
        .name = "colin",
        .parent_directory_address = 0x13200 / 512 + 3,
        .index_address = 0,
    },
    .directory_12 = {
        .signature = FILESYSTEM_SIGNATURE_DIRECTORY,
        .name = "other user",
        .parent_directory_address = 0x13200 / 512 + 3,
        .index_address = 0,
    },
};