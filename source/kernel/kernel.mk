KN_OBJ_DIR=$(OBJ_DIR)/32/kernel/src
KN_OBJS=$(KN_OBJ_DIR)/entry.o $(KN_OBJ_DIR)/heap.o $(KN_OBJ_DIR)/bios_console.o
OBJECTS+=$(KN_OBJS)
INCLUDE_DIRS+=source/kernel/include

.PHONY: kernel
kernel: $(KN_OBJS)