$(BIN_DIR)/filesystem.bin: mkfs $(BIN_DIR)/kernel.bin
	mkdir -p $(BIN_DIR)/root
	cp $(BIN_DIR)/kernel.bin $(BIN_DIR)/root/kernel.bin

	for i in {1..100}; do \
		echo "Test" >> $(BIN_DIR)/root/hello; \
	done

	mkdir -p $(BIN_DIR)/root/test_folder
	echo "This is a test file" > $(BIN_DIR)/root/test_folder/test_file.txt

	$(TOOLS_DIR)/mkfs/build/mkfs $(BIN_DIR)/root $(BIN_DIR)/filesystem.bin