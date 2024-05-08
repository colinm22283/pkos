KN_SOURCE_DIR=$(SOURCE_DIR)/kernel
KN_OD_64=$(OBJ_DIR)/64/kernel/src

export INCLUDE_DIRS+=$(CURDIR)/include

KN_OBJS+=$(KN_OD_64)/driver/disc_pio.o
KN_OBJS+=$(KN_OD_64)/driver/driver_interface.o
KN_OBJS+=$(KN_OD_64)/driver/driver.o

KN_OBJS+=$(KN_OD_64)/util/memory/memcpy.o
KN_OBJS+=$(KN_OD_64)/util/memory/memset.o

KN_OBJS+=$(KN_OD_64)/util/string/strcmp.o
KN_OBJS+=$(KN_OD_64)/util/string/strcmpn.o
KN_OBJS+=$(KN_OD_64)/util/string/strlen.o
KN_OBJS+=$(KN_OD_64)/util/string/strcpy.o

KN_OBJS+=$(KN_OD_64)/paging/tables.o
KN_OBJS+=$(KN_OD_64)/paging/map_kernel.o
KN_OBJS+=$(KN_OD_64)/paging/allocator.o
KN_OBJS+=$(KN_OD_64)/paging/memory_map.o

KN_OBJS+=$(KN_OD_64)/filesystem/filesystem.o

KN_OBJS+=$(KN_OD_64)/entry.o
KN_OBJS+=$(KN_OD_64)/entry_error.o

$(BIN_DIR)/kernel.bin: $(KN_OBJS) $(KN_SOURCE_DIR)/kernel.ld
	mkdir -p $(BIN_DIR)
	$(LD64) $(LDFLAGS) -T$(KN_SOURCE_DIR)/kernel.ld $(KN_OBJS) -o $@ -Map=$@.map

.PHONY: drivers
drivers:
	cd drivers && $(MAKE)

include $(MAKE_SCRIPTS)