cmake_minimum_required (VERSION 3.10)
project(pkos.img LANGUAGES ASM C CXX)

enable_language(ASM)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/build")

set(CMAKE_CXX_COMPILER "/usr/local/cross/bin/i686-elf-g++")
set(CMAKE_C_COMPILER "/usr/local/cross/bin/i686-elf-gcc")
set(CMAKE_ASM_COMPILER "/usr/local/cross/bin/i686-elf-gcc")
#"-MD -std=c99 -m32 -ffreestanding -fno-exceptions -nostdlib -fno-stack-protector -Wall -Wextra -lgcc"
set(CMAKE_EXE_LINKER_FLAGS "-ffreestanding -O2 -nostdlib -lgcc")

add_subdirectory(source)