KN_SOURCE_DIR=$(SOURCE_DIR)/kernel
KN_OD_64=$(OBJ_DIR)/64/kernel/src

export INCLUDE_DIRS+=$(CURDIR)/include

KN_OBJS+=$(KN_OD_64)/driver/driver_table.o

KN_OBJS+=$(KN_OD_64)/util/memory/memcpy.o
KN_OBJS+=$(KN_OD_64)/util/memory/memset.o

KN_OBJS+=$(KN_OD_64)/util/string/strcmp.o
KN_OBJS+=$(KN_OD_64)/util/string/strcmpn.o
KN_OBJS+=$(KN_OD_64)/util/string/strlen.o
KN_OBJS+=$(KN_OD_64)/util/string/strcpy.o

KN_OBJS+=$(KN_OD_64)/util/math/pow.o

KN_OBJS+=$(KN_OD_64)/paging/tables.o
KN_OBJS+=$(KN_OD_64)/paging/init.o
KN_OBJS+=$(KN_OD_64)/paging/region.o
KN_OBJS+=$(KN_OD_64)/paging/bitmap.o
KN_OBJS+=$(KN_OD_64)/paging/map.o

KN_OBJS+=$(KN_OD_64)/memory/memory_map.o
KN_OBJS+=$(KN_OD_64)/memory/primary_region.o

KN_OBJS+=$(KN_OD_64)/module/load.o

KN_OBJS+=$(KN_OD_64)/filesystem/filesystem.o

#KN_OBJS+=$(KN_OD_64)/modules/video_bios/bitmap.o
#KN_OBJS+=$(KN_OD_64)/modules/video_bios/image.o
#KN_OBJS+=$(KN_OD_64)/modules/video_bios/main.o
#KN_OBJS+=$(KN_OD_64)/modules/video_bios/modes.o
#KN_OBJS+=$(KN_OD_64)/modules/video_bios/pixel.o
#KN_OBJS+=$(KN_OD_64)/modules/video_bios/rect.o

KN_OBJS+=$(KN_OD_64)/modules/disc_pio/disc_pio.o

KN_OBJS+=$(KN_OD_64)/entry.o
KN_OBJS+=$(KN_OD_64)/entry_error.o

OPTIMIZATION=1

$(BIN_DIR)/kernel.bin: $(KN_OBJS) $(KN_SOURCE_DIR)/kernel.ld
	mkdir -p $(BIN_DIR)
	$(LD64) $(LDFLAGS) -T$(KN_SOURCE_DIR)/kernel.ld $(KN_OBJS) -o $@ -Map=$@.map

.PHONY: modules
modules:
	cd $(TOOLS_DIR)/mkmod && $(MAKE)
	cd modules && $(MAKE)

include $(MAKE_SCRIPTS)
