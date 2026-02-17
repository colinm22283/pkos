IMAGE_SIZE=2064384

BUILD_DIR=build

BOOTLOADER_BIN=pkbl/build/bin/pkbl.bin
INSTALLER_BIN=installer/build/bin/installer.bin
KERNEL_BIN=pkernel/build/bin/kernel.bin
FS_BIN=$(BUILD_DIR)/pkfs.bin
IMAGE=$(BUILD_DIR)/pkos.img
INSTALLABLE=$(BUILD_DIR)/installable.img
TMP_DISC=$(BUILD_DIR)/tmp_disc.img

PKFS_MKFS=pkfs_tools/mkfs/build/mkfs

.PHONY: all
all: image

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR)
	
	cd pkbl && $(MAKE) clean
	cd installer && $(MAKE) clean
	cd pkernel && $(MAKE) clean
	cd applications && $(MAKE) clean
	cd pkfs_tools/mkfs && $(MAKE) clean

.PHONY: image
image: $(IMAGE)

$(IMAGE): filesystem bootloader
	cat $(BOOTLOADER_BIN) $(FS_BIN) > $(IMAGE)
	truncate $(IMAGE) -s $(IMAGE_SIZE)

.PHONY: installable
installable: $(INSTALLABLE)

$(INSTALLABLE): installer $(IMAGE)
	cat $(INSTALLER_BIN) $(IMAGE) > $(INSTALLABLE)

.PHONY: filesystem
filesystem: $(FS_BIN)

$(FS_BIN): $(BUILD_DIR)/fsroot applications kernel pkfs_mkfs
	cp $(KERNEL_BIN) $(BUILD_DIR)/fsroot/boot/kernel
	
	$(PKFS_MKFS) $(BUILD_DIR)/fsroot $(FS_BIN)

$(BUILD_DIR)/fsroot: $(wildcard fsroot/**)
	mkdir -p $(BUILD_DIR)
	rm -rf $(BUILD_DIR)/fsroot
	cp -r fsroot $(BUILD_DIR)/fsroot

.PHONY: bootloader
bootloader: $(BOOTLOADER_BIN)

.PHONY: installer
installer: $(INSTALLER_BIN)

.PHONY: kernel
kernel: $(KERNEL_BIN)

$(BOOTLOADER_BIN): .FORCE
	cd pkbl && $(MAKE)
	truncate $(BOOTLOADER_BIN) -s 32768

$(INSTALLER_BIN): .FORCE
	cd installer && $(MAKE)

$(KERNEL_BIN): .FORCE
	cd pkernel && $(MAKE)

.PHONY: config
config:
	cd pkernel && $(MAKE) config

.PHONY: config-load
config-load:
	cd pkernel && CONFIG_PATH=$(abspath configs/$(CONFIG_NAME)) $(MAKE) config-load

.PHONY: config-save
config-save:
	cd pkernel && CONFIG_PATH=$(abspath configs/$(CONFIG_NAME)) $(MAKE) config-save

.PHONY: applications
applications: .FORCE fsroot
	cd applications && $(MAKE) KERNEL_DIR=$(CURDIR)/pkernel EXE_DIR=$(CURDIR)/$(BUILD_DIR)/fsroot/bin

.PHONY: mkfs
pkfs_mkfs:
	cd pkfs_tools/mkfs && $(MAKE)

.PHONY: emulate
emulate: $(IMAGE)
	qemu-system-x86_64 -no-reboot -drive file=$(IMAGE),format=raw -vga std -serial stdio -m 6G

.PHONY: emulate-nogui
emulate-nogui: $(IMAGE)
	truncate $(TMP_DISC) -s $(IMAGE_SIZE)
	qemu-system-x86_64 -nographic -no-reboot -drive file=$(IMAGE),format=raw -drive file=$(TMP_DISC),format=raw -vga std -m 6G

.PHONY: emulate-int
emulate-int: $(IMAGE)
	qemu-system-x86_64 -no-reboot -drive file=$(IMAGE),format=raw -vga std -d int -m 6G

.PHONY: emulate-nobuild
emulate-nobuild:
	qemu-system-x86_64 -no-reboot -drive file=$(IMAGE),format=raw -vga std -d int -m 6G

.PHONY: emulate-gdb
emulate-gdb: $(IMAGE)
	qemu-system-x86_64 -no-reboot -s -S -drive file=$(IMAGE),format=raw -vga std -d int -m 6G

.PHONY: emulate-installer
emulate-installer: $(INSTALLABLE)
	truncate $(TMP_DISC) -s $(IMAGE_SIZE)
	qemu-system-x86_64 -no-reboot -drive file=$(INSTALLABLE),format=raw -drive file=$(TMP_DISC),format=raw -vga std -serial stdio -m 6G
	
	qemu-system-x86_64 -no-reboot -drive file=$(TMP_DISC),format=raw -vga std -serial stdio -m 6G

.PHONY: linecount
linecount:
	./scripts/linecount.sh

.PHONY: disc
disc: installable
	$(if $(DISC_TARGET),,echo "DISC_TARGET environment variable not specified!" && false)
	
	$(if $(wildcard $(DISC_TARGET)),,echo "Specified device does not exist!" && false)
	
	sudo dd if=$(INSTALLABLE) of=$(DISC_TARGET) status=progress
	sync

.FORCE:
