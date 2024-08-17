export CC16=/opt/cross/bin/i686-elf-gcc
export CC32=/opt/cross/bin/i686-elf-gcc
export CC64=/opt/cross64/bin/x86_64-elf-gcc

export CXX16=/opt/cross/bin/i686-elf-g++
export CXX32=/opt/cross/bin/i686-elf-g++
export CXX64=/opt/cross64/bin/x86_64-elf-g++

export ASM16=/opt/cross/bin/i686-elf-as
export ASM32=/opt/cross/bin/i686-elf-as
export ASM64=/opt/cross64/bin/x86_64-elf-as

export LD32=/opt/cross/bin/i686-elf-ld
export LD64=/opt/cross64/bin/x86_64-elf-ld

export CFLAGS=-c -ffreestanding -fno-exceptions -nostdlib -fno-stack-protector -fno-asynchronous-unwind-tables -mno-red-zone -Wall -Wextra
export CFLAGS16=-m16 $(CFLAGS)
export CFLAGS32=-m32 $(CFLAGS)
export CFLAGS64=-m64 -mcmodel=large $(CFLAGS)
export CXXFLAGS16=-fno-rtti $(CFLAGS16)
export CXXFLAGS32=-fno-rtti $(CFLAGS32)
export CXXFLAGS64=-fno-rtti $(CFLAGS64)
export ASMFLAGS=

export BUILD_DIR=$(CURDIR)/build
export BIN_DIR=$(BUILD_DIR)/bin
export MODULE_DIR=$(BIN_DIR)/module
export OBJ_DIR=$(BUILD_DIR)/obj
export SOURCE_DIR=$(CURDIR)/source
export TOOLS_DIR=$(CURDIR)/tools

export MAKE_DIR=$(CURDIR)/make
export MAKE_SCRIPTS=$(MAKE_DIR)/targets16.mk $(MAKE_DIR)/targets32.mk $(MAKE_DIR)/targets64.mk

export LDSCRIPTS=$(SOURCE_DIR)/linker/memory.ld $(SOURCE_DIR)/linker/global.ld
export LDFLAGS=$(foreach d, $(LDSCRIPTS), -T$d)

export INCLUDE_DIRS=$(SOURCE_DIR)/system/include

.PHONY: all
all: $(BUILD_DIR)/pkos.img

.PHONY: clean
clean:
	rm -rf $(OBJ_DIR)
	rm -rf $(BIN_DIR)
	rm -f $(BUILD_DIR)/*.img

	cd tools/mkfs && $(MAKE) clean

.PHONY: rebuild
rebuild:
	make clean
	make all

include make/image.mk
include make/filesystem.mk
include $(MAKE_SCRIPTS)

.PHONY: kernel
kernel: $(BIN_DIR)/kernel.bin
.PHONY: bootloader
bootloader: $(BIN_DIR)/bootloader.bin
.PHONY: bootsector
bootsector: $(BIN_DIR)/bootsector.bin
.PHONY: image
image: $(BUILD_DIR)/pkos.img

.PHONY: $(BIN_DIR)/kernel.bin
$(BIN_DIR)/kernel.bin:
	cd source/kernel && $(MAKE)

.PHONY: $(BIN_DIR)/bootloader.bin
$(BIN_DIR)/bootloader.bin:
	cd source/bootloader && $(MAKE)

.PHONY: $(BIN_DIR)/bootsector.bin
$(BIN_DIR)/bootsector.bin:
	cd source/bootsector && $(MAKE)

.PHONY: modules
modules:
	cd source/kernel && $(MAKE) modules

.PHONY: linecount
linecount:
	sh $(MAKE_DIR)/linecount.sh

.PHONY: mkfs
mkfs:
	cd $(TOOLS_DIR)/mkfs && $(MAKE)