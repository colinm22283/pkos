.code32

.global int_fatal_handler_entry
int_fatal_handler_entry:
    cli
    jmp int_fatal_handler