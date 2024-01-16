include make/config.mk

CC16=/usr/local/cross/bin/i686-elf-gcc
CC32=/usr/local/cross/bin/i686-elf-gcc
CC64=/usr/local/cross64/bin/x86_64-elf-gcc

CXX16=/usr/local/cross/bin/i686-elf-g++
CXX32=/usr/local/cross/bin/i686-elf-g++
CXX64=/usr/local/cross64/bin/x86_64-elf-g++

ASM16=/usr/local/cross/bin/i686-elf-as
ASM32=/usr/local/cross/bin/i686-elf-as
ASM64=/usr/local/cross64/bin/x86_64-elf-as

LD32=/usr/local/cross/bin/i686-elf-ld
LD64=/usr/local/cross64/bin/x86_64-elf-ld

CFLAGS=-c -ffreestanding -fno-exceptions -nostdlib -fno-stack-protector -fno-asynchronous-unwind-tables -mno-red-zone -Wall -Wextra
CFLAGS16=-m16 $(CFLAGS)
CFLAGS32=-m32 $(CFLAGS)
CFLAGS64=-m64 -mcmodel=large $(CFLAGS)
CXXFLAGS16=-fno-rtti $(CFLAGS16)
CXXFLAGS32=-fno-rtti $(CFLAGS32)
CXXFLAGS64=-fno-rtti $(CFLAGS64)
ASMFLAGS=

LDSCRIPTS=$(SOURCE_DIR)/linker/memory.ld
LDFLAGS=$(foreach d, $(LDSCRIPTS), -T$d)

BUILD_DIR=build
BIN_DIR=$(BUILD_DIR)/bin
OBJ_DIR=$(BUILD_DIR)/obj
SOURCE_DIR=source

INCLUDE_DIRS=source/system/include

CFLAGS+=-O$(OPTIMIZATION)

.PHONY: all
all: $(BUILD_DIR)/pkos.img

.PHONY: clean
clean:
	rm -rf $(OBJ_DIR)
	rm -rf $(BIN_DIR)
	rm -f $(BUILD_DIR)/*.img

.PHONY: full
full:
	make clean
	make all

include $(SOURCE_DIR)/bootsector/bootsector.mk
include $(SOURCE_DIR)/bootloader/bootloader.mk

include make/image.mk

include make/targets16.mk
include make/targets32.mk
include make/targets64.mk