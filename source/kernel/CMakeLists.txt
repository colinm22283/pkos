add_library(kernel src/entry.cpp)
target_include_directories(kernel PUBLIC include)
target_link_libraries(kernel PUBLIC system)
target_compile_options(kernel PUBLIC -m32 -fno-rtti -ffreestanding -fno-exceptions -nostdlib -fno-stack-protector -Wall -Wextra -lgcc)