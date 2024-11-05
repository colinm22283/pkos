#include <memory/palloc/palloc.h>

#include <memory/palloc/allocation_space.h>

void palloc_init() {
    palloc_tag_t * head_tag = ALLOCATION_SPACE_START;
    palloc_tag_t * tail_tag = (palloc_tag_t *) ((intptr_t) ALLOCATION_SPACE_START + ALLOCATION_SPACE_SIZE - sizeof(palloc_tag_t));
}
