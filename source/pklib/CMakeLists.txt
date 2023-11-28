add_library(pklib src/heap.s src/init.c)
target_include_directories(pklib PUBLIC include)
target_link_libraries(pklib PUBLIC system)
target_compile_options(pklib PUBLIC -m${BITS} -ffreestanding -fno-exceptions -nostdlib -fno-stack-protector -Wall -Wextra -lgcc)