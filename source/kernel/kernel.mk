KN_OBJ_DIR=$(OBJ_DIR)/kernel/src
KN_OBJS=$(KN_OBJ_DIR)/entry.o
OBJECTS+=$(KN_OBJS)
INCLUDE_DIRS+=source/kernel/include

include make/targets32.mk

.PHONY: kernel
kernel: $(KN_OBJS)