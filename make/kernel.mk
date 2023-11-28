KN_OBJ_DIR=$(OBJ_DIR)/kernel
KN_OBJS=$(KN_OBJ_DIR)/test.o
OBJECTS+=$(KN_OBJS)

include make/targets32.mk



.PHONY: kernel
kernel: $(KN_OBJS)