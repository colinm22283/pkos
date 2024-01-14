BL32_SOURCE_DIR=$(SOURCE_DIR)/bootloader32
BL32_OD_32=$(OBJ_DIR)/32/bootloader32
BL32_OBJS=$(BL32_OD_32)/bootloader32.o $(BL32_OD_32)/gdt32.o

$(BIN_DIR)/bootloader32.bin: $(BL32_OBJS) $(BL32_SOURCE_DIR)/bootloader32.ld $(LDSCRIPT)
	mkdir -p $(BIN_DIR)
	$(LD32) $(LDFLAGS) -T$(BL32_SOURCE_DIR)/bootloader32.ld $(BL32_OBJS) -o $@
	truncate $@ -s 512