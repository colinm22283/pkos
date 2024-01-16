.code32

.section .bootloader, "a"

.global console_ptr
console_ptr: .long 0xB8000

.global newline_ptr
newline_ptr: .long 0xB8000 + 80
