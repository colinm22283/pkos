KN_SOURCE_DIR=$(SOURCE_DIR)/kernel
KN_OD_64=$(OBJ_DIR)/64/kernel/src

INCLUDE_DIRS+=$(CURDIR)/include

KN_OBJS+=$(KN_OD_64)/driver_table/driver_table.o

KN_OBJS+=$(KN_OD_64)/driver/disc_pio.o
KN_OBJS+=$(KN_OD_64)/driver/video_bios.o

KN_OBJS+=$(KN_OD_64)/main.o

$(BIN_DIR)/kernel.bin: $(KN_OBJS) $(KN_SOURCE_DIR)/kernel.ld
	mkdir -p $(BIN_DIR)
	$(LD64) $(LDFLAGS) -T$(KN_SOURCE_DIR)/kernel.ld $(KN_OBJS) -o $@ -Map=$@.map
	truncate $@ -s 65536

include $(MAKE_SCRIPTS)