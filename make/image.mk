$(BUILD_DIR)/pkos.img: $(BIN_DIR)/bootloader.bin $(BIN_DIR)/bootsector.bin $(BIN_DIR)/filesystem.bin
	cat $(BIN_DIR)/bootsector.bin $(BIN_DIR)/bootloader.bin $(BIN_DIR)/filesystem.bin > $(BUILD_DIR)/pkos.img