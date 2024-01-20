.code32

.global int_fatal_handler
int_fatal_handler:
    cli

    .halt_loop:
        hlt
        jmp .halt_loop
