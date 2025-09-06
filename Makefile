IMAGE_SIZE=2064384

BUILD_DIR=build

BOOTLOADER_BIN=pkbl/build/bin/pkbl.bin
KERNEL_BIN=pkernel/build/bin/kernel.bin
FS_BIN=$(BUILD_DIR)/pkfs.bin
IMAGE=$(BUILD_DIR)/pkos.img

PKFS_MKFS=pkfs_tools/mkfs/build/mkfs

.PHONY: all
all: image

.PHONY: clean
clean:
	cd pkbl && $(MAKE) clean
	cd pkernel && $(MAKE) clean
	cd pkfs_tools/mkfs && $(MAKE) clean

.PHONY: image
image: $(IMAGE)

$(IMAGE): filesystem bootloader
	cat $(BOOTLOADER_BIN) $(FS_BIN) > $(IMAGE)
	truncate $(IMAGE) -s $(IMAGE_SIZE)

.PHONY: filesystem
filesystem: $(FS_BIN)

$(FS_BIN): $(BUILD_DIR)/fsroot kernel pkfs_mkfs
	cp $(KERNEL_BIN) $(BUILD_DIR)/fsroot/boot/kernel
	
	$(PKFS_MKFS) $(BUILD_DIR)/fsroot $(FS_BIN)

$(BUILD_DIR)/fsroot: fsroot
	mkdir -p $(BUILD_DIR)
	cp -r fsroot $(BUILD_DIR)/fsroot

.PHONY: bootloader
bootloader: $(BOOTLOADER_BIN)

.PHONY: kernel
kernel: $(KERNEL_BIN)

$(BOOTLOADER_BIN): .FORCE
	cd pkbl && $(MAKE)
	truncate $(BOOTLOADER_BIN) -s 32768

$(KERNEL_BIN): .FORCE
	cd pkernel && $(MAKE)

.PHONY: mkfs
pkfs_mkfs:
	cd pkfs_tools/mkfs && $(MAKE)

.PHONY: emulate
emulate: $(IMAGE)
	qemu-system-x86_64 -no-reboot -drive file=$(IMAGE),format=raw -vga std -d int -m 6G

.PHONY: emulate-nobuild
emulate-nobuild: $(IMAGE)
	qemu-system-x86_64 -no-reboot -drive file=$(IMAGE),format=raw -vga std -d int -m 6G

.PHONY: emulate-gdb
emulate-gdb: $(IMAGE)
	qemu-system-x86_64 -no-reboot -s -S -drive file=$(IMAGE),format=raw -vga std -d int -m 6G

.FORCE:
