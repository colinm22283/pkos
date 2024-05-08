DISC_SIZE=32256

export FILESYSTEM_ROOT=$(BIN_DIR)/root

$(BIN_DIR)/filesystem.bin: mkfs kernel drivers
	mkdir -p $(FILESYSTEM_ROOT)

	mkdir -p $(FILESYSTEM_ROOT)/boot
	cp $(BIN_DIR)/kernel.bin $(FILESYSTEM_ROOT)/boot/kernel

	mkdir -p $(FILESYSTEM_ROOT)/boot/driver
	cp $(DRIVER_DIR)/*.drv $(FILESYSTEM_ROOT)/boot/driver

	mkdir -p $(FILESYSTEM_ROOT)/home
	echo "This is a test file 1" > $(FILESYSTEM_ROOT)/home/test_file_1.txt
	echo "This is a test file 2" > $(FILESYSTEM_ROOT)/home/test_file_2.txt

	$(TOOLS_DIR)/mkfs/build/mkfs $(FILESYSTEM_ROOT) $(BIN_DIR)/filesystem.bin

	truncate $(BIN_DIR)/filesystem.bin -s $(DISC_SIZE)