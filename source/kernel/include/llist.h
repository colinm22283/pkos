#pragma once

#include <stddef.h>

#include <memory/heap.h>

typedef struct llist_node_s {
    int value;
    struct llist_node_s * next;
} llist_node_t;

typedef struct {
    llist_node_t * head;
} llist_t;

static inline void llist_init(llist_t * llist) {
    llist->head = NULL;
}

static inline int * llist_add(llist_t * llist, int ele) {
    llist_node_t * temp = llist->head;
    llist->head = _heap_alloc(sizeof(llist_node_t));
    llist->head->next = temp;
    llist->head->value = ele;
    return &llist->head->value;
}

static inline void llist_pop(llist_t * llist) {
    llist_node_t * temp = llist->head;
    llist->head = llist->head->next;
    if (_heap_free(temp)) print_string("HEAP ERROR!\n");
}

static inline void llist_free(llist_t * llist) {
    llist_node_t * node = llist->head;
    while (node != NULL) {
        llist_node_t * temp = node->next;
        _heap_free(node);
        node = temp;
    }
}