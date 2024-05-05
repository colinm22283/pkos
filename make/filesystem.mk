DISC_SIZE=32256

$(BIN_DIR)/root/kernel: $(BIN_DIR)/kernel.bin
	mkdir -p $(BIN_DIR)/root
	cp $(BIN_DIR)/kernel.bin $(BIN_DIR)/root/kernel


$(BIN_DIR)/filesystem.bin: mkfs $(BIN_DIR)/root/kernel
	for i in {1..100}; do \
		echo "Test" >> $(BIN_DIR)/root/hello; \
	done

	mkdir -p $(BIN_DIR)/root/test_folder
	echo "This is a test file 1" > $(BIN_DIR)/root/test_folder/test_file_1.txt
	echo "This is a test file 2" > $(BIN_DIR)/root/test_folder/test_file_2.txt

	mkdir -p $(BIN_DIR)/root/test_folder/folder_2
	echo "This is a test file 3" > $(BIN_DIR)/root/test_folder/folder_2/test_file_3.txt

	$(TOOLS_DIR)/mkfs/build/mkfs $(BIN_DIR)/root $(BIN_DIR)/filesystem.bin

	truncate $(BIN_DIR)/filesystem.bin -s $(DISC_SIZE)