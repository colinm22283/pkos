.code64

.section .bootloader, "a"
.global long_mode_entry
long_mode_entry:
    hlt
