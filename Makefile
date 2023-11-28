CC16=/usr/local/cross/bin/i686-elf-gcc
CC32=/usr/local/cross/bin/i686-elf-gcc
CXX16=/usr/local/cross/bin/i686-elf-gcc
CXX32=/usr/local/cross/bin/i686-elf-gcc
ASM=/usr/local/cross/bin/i686-elf-as
LD=/usr/local/cross/bin/i686-elf-ld

CFLAGS=-c -ffreestanding -fno-exceptions -nostdlib -fno-stack-protector -Wall -Wextra -lgcc
CFLAGS16=-m16 $(CFLAGS)
CFLAGS32=-m32 $(CFLAGS)
CXXFLAGS16=-fno-rtti $(CFLAGS16)
CXXFLAGS32=-fno-rtti $(CFLAGS32)
ASMFLAGS=

LDSCRIPTS=source/linker/bootloader.ld
LDFLAGS=$(foreach d, $(LDSCRIPTS), -T$d)

BUILD_DIR=build
OBJ_DIR=$(BUILD_DIR)/obj
SOURCE_DIR=source

INCLUDE_DIRS=source/system/include
OBJECTS=

.PHONY: all
all: $(BUILD_DIR)/pkos.img

.PHONY: clean
clean:
	mkdir -p $(OBJ_DIR)
	rm -rf $(OBJ_DIR)/*
	rm -f $(BUILD_DIR)/*.img
	rm -f $(BUILD_DIR)/*.bin

include make/targets.mk
include make/targets16.mk
include make/targets32.mk
include make/targets64.mk

include source/bootloader/bootloader.mk
include source/kernel/kernel.mk
include make/link.mk
include make/image.mk