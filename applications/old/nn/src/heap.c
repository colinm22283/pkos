#include <stddef.h>
#include <stdint.h>

#include <heap.h>
#include <memset.h>
#include <memcpy.h>

uint64_t alloc_size;
char heap_data[HEAP_INITIAL_SIZE];
heap_tag_t * head_tag;
heap_tag_t * tail_tag;

void heap_init(void) {
    alloc_size = 0;

    uint64_t sector_size = HEAP_INITIAL_SIZE - 2 * sizeof(heap_tag_t);

    head_tag = (heap_tag_t *) heap_data;
    tail_tag = (heap_tag_t *) ((intptr_t) heap_data + sector_size + sizeof(heap_tag_t));

    head_tag->next_size = sector_size;
    head_tag->prev_size = 0;
    head_tag->next_reserved = false;

    tail_tag->prev_size = sector_size;
    tail_tag->next_size = 0;
    tail_tag->next_reserved = false;
}

void * heap_alloc(uint64_t size_bytes) {
    if (size_bytes == 0) NULL;

    heap_tag_t * current_tag = head_tag;

    alloc_size += size_bytes;

    while (
        current_tag->next_reserved ||
        (
            current_tag->next_size <= size_bytes + sizeof(heap_tag_t) &&
            current_tag->next_size != size_bytes
        )
    ) {
        current_tag = (heap_tag_t *) ((uint64_t) current_tag + current_tag->next_size + sizeof(heap_tag_t));

        if (current_tag->next_size == 0) {
            return NULL;
        }
    }

    if (current_tag->next_size == size_bytes) {
        current_tag->next_reserved = true;
    }
    else {
        heap_tag_t * next_tag = (heap_tag_t *) ((intptr_t) current_tag + current_tag->next_size + sizeof(heap_tag_t));
        heap_tag_t * mid_tag = (heap_tag_t *) ((intptr_t) current_tag + size_bytes + sizeof(heap_tag_t));

        if (current_tag->next_reserved) return NULL;

        if (current_tag->next_size != next_tag->prev_size) return NULL;

        uint64_t remaining_bytes = current_tag->next_size - size_bytes - sizeof(heap_tag_t);

        current_tag->next_size = size_bytes;
        current_tag->next_reserved = true;

        mid_tag->prev_size = size_bytes;
        mid_tag->next_size = remaining_bytes;
        mid_tag->next_reserved = false;

        next_tag->prev_size = remaining_bytes;
    }

    memset((char *) (current_tag + 1), 0, size_bytes);

    return current_tag + 1;
}

void heap_free(void * alloc) {
    heap_tag_t * tag = ((heap_tag_t *) alloc) - 1;

    alloc_size -= tag->next_size;

    if (!tag->next_reserved) return;

    heap_tag_t * next_tag = (heap_tag_t *) ((intptr_t) tag + tag->next_size + sizeof(heap_tag_t));

    if (tag->next_size != next_tag->prev_size) {
        return;
    }

    if (!next_tag->next_reserved && next_tag->next_size != 0) {
        tag->next_size += next_tag->next_size + sizeof(heap_tag_t);

        if (next_tag->next_size != 0) {
            heap_tag_t * next_next_tag = (heap_tag_t *) ((intptr_t) next_tag + next_tag->next_size + sizeof(heap_tag_t));
            next_next_tag->prev_size = tag->next_size;

            next_tag = next_next_tag;
        }
    }

    next_tag->prev_size = tag->next_size;

    if (tag->prev_size != 0) {
        heap_tag_t * prev_tag = (heap_tag_t *) ((intptr_t) tag - tag->prev_size - sizeof(heap_tag_t));
        if (!prev_tag->next_reserved) {
            prev_tag->next_size += tag->next_size + sizeof(heap_tag_t);

            next_tag->prev_size = prev_tag->next_size;

            return;
        }
    }

    tag->next_reserved = false;
}

void * heap_realloc(void * alloc, uint64_t size_bytes) {
    heap_tag_t * tag = ((heap_tag_t *) alloc) - 1;

    void * new_buffer = heap_alloc(size_bytes);
    memcpy(new_buffer, alloc, tag->next_size);

    heap_free(alloc);

    return new_buffer;
}
