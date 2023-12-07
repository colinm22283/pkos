BL_OBJ_DIR=$(OBJ_DIR)/bootloader
BL_OBJ_DIR_32=$(OBJ_DIR)/32/bootloader
BL_OBJS=$(BL_OBJ_DIR)/bootloader.o $(BL_OBJ_DIR_32)/gdt.o
OBJECTS+=$(BL_OBJS)

.PHONY: bootloader
bootloader: $(BL_OBJS)