DISC_SIZE=516096

export FILESYSTEM_ROOT=$(BIN_DIR)/root

$(FILESYSTEM_ROOT):
	mkdir -p $(FILESYSTEM_ROOT)

$(FILESYSTEM_ROOT)/boot: $(FILESYSTEM_ROOT)
	mkdir -p $(FILESYSTEM_ROOT)/boot

$(FILESYSTEM_ROOT)/boot/kernel: $(FILESYSTEM_ROOT)/boot $(BIN_DIR)/kernel.bin
	cp $(BIN_DIR)/kernel.bin $(FILESYSTEM_ROOT)/boot/kernel

$(FILESYSTEM_ROOT)/boot/version.txt: $(FILESYSTEM_ROOT)/boot
	echo "v0.1" > $(FILESYSTEM_ROOT)/boot/version.txt

$(FILESYSTEM_ROOT)/boot/modules: $(FILESYSTEM_ROOT)/boot modules
	mkdir -p $(FILESYSTEM_ROOT)/boot/modules
	cp $(MODULE_DIR)/*.mod $(FILESYSTEM_ROOT)/boot/modules || true

$(FILESYSTEM_ROOT)/home: $(FILESYSTEM_ROOT)
	mkdir -p $(FILESYSTEM_ROOT)/home

$(FILESYSTEM_ROOT)/home/test_file.txt: $(FILESYSTEM_ROOT)/home
	echo "This is a test file!" > $(FILESYSTEM_ROOT)/home/test_file.txt

$(FILESYSTEM_ROOT)/home/smile.bmp: $(FILESYSTEM_ROOT)/home
	echo -n -e \\x00\\x44\\x44\\x00\\x82\\x44\\x38 > $(FILESYSTEM_ROOT)/home/smile.bmp

$(BIN_DIR)/filesystem.bin: $(FILESYSTEM_ROOT)/boot/kernel $(FILESYSTEM_ROOT)/boot/version.txt $(FILESYSTEM_ROOT)/boot/modules $(FILESYSTEM_ROOT)/home/test_file.txt $(FILESYSTEM_ROOT)/home/smile.bmp mkfs
	$(TOOLS_DIR)/mkfs/build/mkfs $(FILESYSTEM_ROOT) $(BIN_DIR)/filesystem.bin

	truncate $(BIN_DIR)/filesystem.bin -s $(DISC_SIZE)