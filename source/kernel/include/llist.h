#pragma once

#include <stddef.h>

#include "memory/heap.h"

typedef struct llist_node_s {
    uint32_t value;
    struct llist_node_s * next;
} llist_node_t;

typedef struct {
    llist_node_t * head;
} llist_t;

static inline void llist_init(llist_t * llist) {
    llist->head = NULL;
}

static inline uint32_t * llist_add(llist_t * llist, uint32_t ele) {
    llist_node_t * temp = llist->head;
    llist->head = (llist_node_t *) heap_alloc(sizeof(llist_node_t));
    llist->head->next = temp;
    llist->head->value = ele;
    return &llist->head->value;
}

static inline void llist_pop(llist_t * llist) {
    llist_node_t * temp = llist->head;
    llist->head = llist->head->next;
    heap_free(temp);
}

static inline void llist_free(llist_t * llist) {
    llist_node_t * node = llist->head;
    while (node != NULL) {
        llist_node_t * temp = node->next;
        heap_free(node);
        node = temp;
    }
}