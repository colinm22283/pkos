$(BUILD_DIR)/pkos.img: $(BIN_DIR)/bootloader32.bin $(BIN_DIR)/bootloader64.bin $(BIN_DIR)/kernel.bin
	cat $(BIN_DIR)/bootloader32.bin $(BIN_DIR)/bootloader64.bin $(BIN_DIR)/kernel.bin > $(BUILD_DIR)/pkos.img