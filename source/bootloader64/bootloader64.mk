BL64_SOURCE_DIR=$(SOURCE_DIR)/bootloader64
BL64_OD_64=$(OBJ_DIR)/64/bootloader64
BL64_OBJS=$(BL64_OD_64)/bootloader64.o $(BL64_OD_64)/gdt64.o $(BL64_OD_64)/tss64.o

$(BIN_DIR)/bootloader64.bin: $(BL64_OBJS) $(BL64_SOURCE_DIR)/bootloader64.ld $(LDSCRIPT)
	mkdir -p $(BIN_DIR)
	$(LD64) $(LDFLAGS) -T$(BL64_SOURCE_DIR)/bootloader64.ld $(BL64_OBJS) -o $@
	truncate $@ -s 1024