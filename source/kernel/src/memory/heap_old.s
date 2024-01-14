.code64

# TODO: this need to be brought up to 64 bit so we can alloc more than 4 GiB at a time

.section .text
.global heap_init
.type heap_init, @function
heap_init:
    mov $_heap_base, %eax
    movl $0, (%eax)
    movl $(0x500 - 16), 4(%eax)

    mov $(_heap_top - 8), %eax
    movl $0, (%eax)
    movl $0, 4(%eax)

    ret

.global heap_alloc
.type heap_alloc, @function
heap_alloc:
    push %rbx

    movl %edi, %edx
    add $8, %edx

    mov $(_heap_base + 4), %eax
    # eax contains the current tag address + 4

    .check_next:
        movl (%eax), %ebx
        cmpl $0, %ebx
        je  .not_found
        cmpl $0x80000000, %ebx
        jae .not_avail # ebx >= 0x80000000
        # ebx contains the region size
        cmpl %edx, %ebx
        jae .found # ebx >= edx
    .not_avail:
        and  $0x7FFFFFFF, %ebx
        add %ebx, %eax
        add $8,   %eax
        # now pointing at the next tag + 4

        jmp .check_next

    .found:
        # eax must always be tag + 4
        # ebx must always be the tag size
        # ecx is our temporary register
        # edx must always be the requested size + 8

        push %rax

        sub $8, %edx
        # edx is the requested size

        # write the size for our block
        mov %edx, %ecx
        or  $0x80000000, %ecx
        movl %ecx, (%eax)

        # write the new tag we have in the middle
        add %edx, %eax
        add $4,   %eax
        # now pointing at new tag
        movl %edx, (%eax)
        add $4,   %eax
        sub %edx, %ebx
        sub $8,   %ebx
        # ebx is now the next size
        movl %ebx, (%eax)

        # reduce the next tags prev size
        add %ebx, %eax
        # eax points to start of next tag
        movl %ebx, 4(%eax)

        pop %rax
        add $4, %eax
        pop %rbx
        ret

    .not_found:
        # return nullptr
        mov $0, %eax

        pop %rbx

        ret

.global heap_free
.type heap_free, @function
heap_free:
    test %edi, %edi
    jnz  .not_null
        mov $1, %eax
        ret
    .not_null:

    push %rbx

    movl %edi, %edx
    sub $4, %edx

    movl (%edx), %eax

    # check to make sure this is a valid operation
    mov %eax, %ecx
    cmp $0x80000000, %ecx
    jae .block_valid # ecx >= 0x80000000
    cmp $(_heap_base + 8), %edx
    jae .block_valid # edx >= _heap_base + 8
    cmp $(_heap_top - 8), %edx
    jbe .block_valid # edx <= _heap_top - 8
        mov $1, %eax
        pop %rbx
        pop %rbp
        ret
    .block_valid:

    and $0x7FFFFFFF, %eax

    # eax is the total size to free
    # edx is the tag pointer + 4

    # check ahead first
    movl (%edx), %ecx
    and $0x7FFFFFFF, %ecx
    add %edx, %ecx
    add $8,   %ecx
    # ecx points to the next tag + 4
    movl (%ecx), %ebx
    cmpl $0x80000000, %ebx
    jae .next_is_not_free # ebx >= 0x80000000
        add %ebx, %eax
        add $8,   %eax
    .next_is_not_free:

    sub $4, %edx

    # edx is now the tag pointer

    # now we check behind
    movl (%edx), %ecx
    cmp $0, %ecx
    je  .prev_is_not_free

    mov %edx, %ebx
    sub %ecx, %ebx
    sub $4,   %ebx
    # ebx is previous tag + 4
    movl (%ebx), %ecx
    cmpl $0x80000000, %ecx
    jge .prev_is_not_free
        # write our total size to this block
        add %ecx, %eax
        add $8, %eax
        movl %eax, (%ebx)

        mov $0, %eax
        pop %rbx
        pop %rbp
        ret
    .prev_is_not_free:

    # write our tag to the first block
    add $4, %edx
    movl %eax, (%edx)

    mov $0, %eax
    pop %rbx

    ret