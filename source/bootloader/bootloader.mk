BL_OBJ_DIR=$(OBJ_DIR)/bootloader
BL_OBJS=$(BL_OBJ_DIR)/bootloader.o $(BL_OBJ_DIR)/gdt.o
OBJECTS+=$(BL_OBJS)

include make/targets16.mk

.PHONY: bootloader
bootloader: $(BL_OBJS)