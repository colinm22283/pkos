BL_SOURCE_DIR=$(SOURCE_DIR)/bootloader
BL_OD_32=$(OBJ_DIR)/64/bootloader/src
BL_OD_64=$(OBJ_DIR)/64/bootloader/src

BL_OBJS+=$(BL_OD_32)/bootloader32.o

BL_OBJS+=$(BL_OD_64)/gdt64.o
BL_OBJS+=$(BL_OD_64)/page_tables.o

BL_OBJS+=$(BL_OD_32)/boot_error.o

BL_OBJS+=$(BL_OD_32)/console/print_string.o
BL_OBJS+=$(BL_OD_32)/console/print_hex.o
BL_OBJS+=$(BL_OD_32)/console/print_newline.o
BL_OBJS+=$(BL_OD_32)/console/console.o

BL_OBJS+=$(BL_OD_32)/shell/shell_entry.o

$(BIN_DIR)/bootloader.bin: $(BL_OBJS) $(BL_SOURCE_DIR)/bootloader.ld
	mkdir -p $(BIN_DIR)
	$(LD64) $(LDFLAGS) -T$(BL_SOURCE_DIR)/bootloader.ld $(BL_OBJS) -o $@
	truncate $@ -s 4096