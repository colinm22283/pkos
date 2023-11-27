add_library(bootloader bootloader.s gdt.c)
target_link_libraries(bootloader PUBLIC system)
target_compile_options(bootloader PUBLIC -m16 -ffreestanding -fno-exceptions -nostdlib -fno-stack-protector -Wall -Wextra -lgcc)