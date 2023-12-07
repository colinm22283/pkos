#include <stdint.h>
#include <stdbool.h>

#include <memory/heap.h>
#include <bios_console.h>
#include <llist.h>

static inline void strcpy(char * dst, const char * src) {
    while (*src != '\0') *(dst++) = *(src++);
    *dst = '\0';
}

__attribute__((noreturn)) void _kernel_entry() {
    print_string("Boot Success!\n");

    heap_init();

    llist_t list;
    llist_init(&list);

    llist_add(&list, 1);
    llist_add(&list, 2);
    llist_add(&list, 3);
    llist_add(&list, 4);

    llist_pop(&list);
    llist_pop(&list);

    llist_add(&list, 5);
    llist_add(&list, 6);

    llist_pop(&list);

    llist_add(&list, 7);
    llist_add(&list, 8);
    llist_add(&list, 9);

    llist_node_t * node = list.head;
    while (node != NULL) {
        print_int32(node->value);
        print_char('\n');
        node = node->next;
    }

    llist_free(&list);

    print_string("Done!\n");

    while (true);
}