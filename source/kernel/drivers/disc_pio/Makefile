DRIVER_SOURCE_DIR=$(CURDIR)/src
DRIVER_OD_64=$(OBJ_DIR)/64/kernel/drivers/$(DRIVER_NAME)/src

DRIVER_OBJS=$(DRIVER_OD_64)/main.o $(DRIVER_OD_64)/modes.o $(DRIVER_OD_64)/rect.o $(DRIVER_OD_64)/bitmap.o $(DRIVER_OD_64)/image.o $(DRIVER_OD_64)/pixel.o


INCLUDE_DIRS+=$(CURDIR)/include

$(DRIVER_DIR)/$(DRIVER_NAME).drv: $(DRIVER_OBJS) $(DRIVER_LD_SCRIPT)
	mkdir -p $(DRIVER_DIR)
	$(LD64) $(LDFLAGS) -T$(DRIVER_LD_SCRIPT) $(DRIVER_OBJS) -o $@ -Map=$@.map

include $(MAKE_SCRIPTS)