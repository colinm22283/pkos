add_library(kernel src/entry.c)
target_include_directories(kernel PUBLIC include)
target_link_libraries(kernel PUBLIC system pklib)
target_compile_options(kernel PUBLIC -m${BITS} -ffreestanding -fno-exceptions -nostdlib -fno-stack-protector -Wall -Wextra -lgcc)
#  -fno-rtti