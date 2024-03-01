$(BUILD_DIR)/pkos.img: $(BIN_DIR)/kernel.bin $(BIN_DIR)/bootloader.bin $(BIN_DIR)/bootsector.bin
	cat $(BIN_DIR)/bootsector.bin $(BIN_DIR)/bootloader.bin $(BIN_DIR)/kernel.bin > $(BUILD_DIR)/pkos.img