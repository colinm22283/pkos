include make/config.mk

CC16=/usr/local/cross/bin/i686-elf-gcc
CC32=/usr/local/cross/bin/i686-elf-gcc
#CC64=/usr/local/cross64/bin/x86_64-elf-gcc

CXX16=/usr/local/cross/bin/i686-elf-g++
CXX32=/usr/local/cross/bin/i686-elf-g++
#CXX64=/usr/local/cross64/bin/x86_64-elf-g++

ASM=/usr/local/cross/bin/i686-elf-as
LD=/usr/local/cross/bin/i686-elf-ld

CFLAGS=-c -ffreestanding -fno-exceptions -nostdlib -fno-stack-protector -Wall -Wextra -lgcc
CFLAGS16=-m16 $(CFLAGS)
CFLAGS32=-m32 $(CFLAGS)
CFLAGS64=-m64 -mno-red-zone $(CFLAGS)
CXXFLAGS16=-fno-rtti $(CFLAGS16)
CXXFLAGS32=-fno-rtti $(CFLAGS32)
CXXFLAGS64=-fno-rtti $(CFLAGS64)
ASMFLAGS=

LDSCRIPTS=source/linker/bootloader.ld
LDFLAGS=$(foreach d, $(LDSCRIPTS), -T$d)

BUILD_DIR=build
OBJ_DIR=$(BUILD_DIR)/obj
SOURCE_DIR=source

INCLUDE_DIRS=source/system/include
OBJECTS=

CFLAGS+=-O$(OPTIMIZATION)

.PHONY: all
all: $(BUILD_DIR)/pkos.img

.PHONY: clean
clean:
	rm -rf $(OBJ_DIR)
	rm -f $(BUILD_DIR)/*.img
	rm -f $(BUILD_DIR)/*.bin

.PHONY: full
full:
	make clean
	make all

include source/bootloader/bootloader.mk
include source/kernel/kernel.mk

include make/link.mk
include make/image.mk

include make/targets.mk
include make/targets16.mk
include make/targets32.mk
include make/targets64.mk