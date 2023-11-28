CC16=i686-elf-gcc
CC32=i686-elf-gcc
CXX16=i686-elf-gcc
CXX32=i686-elf-gcc
ASM=i686-elf-as
LD=i686-elf-ld

CFLAGS=-c -ffreestanding -fno-exceptions -nostdlib -fno-stack-protector -Wall -Wextra -lgcc -I source/system/include
CFLAGS16=-m16 $(CFLAGS)
CFLAGS32=-m32 $(CFLAGS)
CXXFLAGS16=-fno-rtti $(CFLAGS16)
CXXFLAGS32=-fno-rtti $(CFLAGS32)
ASMFLAGS=
LDSCRIPT=source/linker/bootloader.ld
LDFLAGS=-T $(LDSCRIPT)

BUILD_DIR=build
OBJ_DIR=$(BUILD_DIR)/obj
SOURCE_DIR=source

OBJECTS=

.PHONY: all
all: $(BUILD_DIR)/pkos.img

.PHONY: clean
clean:
	mkdir -p $(OBJ_DIR)
	rm -rf $(OBJ_DIR)/*
	rm -f $(BUILD_DIR)/*.img
	rm -f $(BUILD_DIR)/*.bin

include make/bootloader.mk
include make/kernel.mk
include make/link.mk
include make/image.mk