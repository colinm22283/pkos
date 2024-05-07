DISC_SIZE=32256

export FILESYSTEM_ROOT=$(BIN_DIR)/root

$(FILESYSTEM_ROOT)/kernel: $(BIN_DIR)/kernel.bin
	mkdir -p $(BIN_DIR)/root
	cp $(BIN_DIR)/kernel.bin $(BIN_DIR)/root/kernel


$(BIN_DIR)/filesystem.bin: mkfs $(FILESYSTEM_ROOT)/kernel
	for i in {1..100}; do \
		echo "Test" >> $(FILESYSTEM_ROOT)/hello; \
	done

	mkdir -p $(FILESYSTEM_ROOT)/test_folder
	echo "This is a test file 1" > $(FILESYSTEM_ROOT)/test_folder/test_file_1.txt
	echo "This is a test file 2" > $(FILESYSTEM_ROOT)/test_folder/test_file_2.txt

	mkdir -p $(BIN_DIR)/root/test_folder/folder_2
	echo "This is a test file 3" > $(FILESYSTEM_ROOT)/test_folder/folder_2/test_file_3.txt

	echo "AbAbAbAbAbAbAbAbAbAbAbAbAbAbAbAbAbAb" > $(FILESYSTEM_ROOT)/test_folder/folder_2/test_image

	$(TOOLS_DIR)/mkfs/build/mkfs $(FILESYSTEM_ROOT) $(BIN_DIR)/filesystem.bin

	truncate $(BIN_DIR)/filesystem.bin -s $(DISC_SIZE)