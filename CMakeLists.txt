cmake_minimum_required (VERSION 3.10)
project(pkos.img LANGUAGES ASM C CXX)

enable_language(ASM)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/build")

set(CMAKE_CXX_COMPILER "/usr/local/cross/bin/i686-elf-g++")
set(CMAKE_C_COMPILER "/usr/local/cross/bin/i686-elf-gcc")
set(CMAKE_ASM_COMPILER "/usr/local/cross/bin/i686-elf-gcc")
#"-MD -std=c99 -m32 -ffreestanding -fno-exceptions -nostdlib -fno-stack-protector -Wall -Wextra -lgcc"
set(CMAKE_CXX_FLAGS "-m32 -fno-rtti -ffreestanding -fno-exceptions -nostdlib -fno-stack-protector -Wall -Wextra -lgcc")
set(CMAKE_C_FLAGS "-m32 -std=gnu99 -ffreestanding -fno-exceptions -nostdlib -fno-stack-protector -Wall -Wextra -lgcc")
set(CMAKE_ASM_FLAGS "-fno-rtti -ffreestanding -fno-exceptions -nostdlib -fno-stack-protector -Wall -Wextra -lgcc")
set(CMAKE_EXE_LINKER_FLAGS "-ffreestanding -O2 -nostdlib -lgcc")

file(GLOB_RECURSE C_SOURCES "source/*.c")
file(GLOB_RECURSE CXX_SOURCES "source/*.cpp")
file(GLOB_RECURSE ASM_SOURCES "source/*.s")

add_executable(pkos.img ${C_SOURCES} ${CXX_SOURCES} ${ASM_SOURCES})

target_include_directories(pkos.img PRIVATE source/kernel/include source/system/include)

file(GLOB_RECURSE LD_SOURCES "source/linker/*.ld")
set_property(TARGET pkos.img PROPERTY LINK_DEPENDS "${LD_SOURCES}")
list(TRANSFORM LD_SOURCES PREPEND "-T")
target_link_options(pkos.img PRIVATE "${LD_SOURCES}")