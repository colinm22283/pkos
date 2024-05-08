DRIVERS=video_bios

export DRIVER_LD_SCRIPT=$(CURDIR)/driver.ld
export CFLAGS+=-fPIC

.PHONY: all
all:
	$(foreach driver, $(DRIVERS), cd $(driver) && $(MAKE) DRIVER_NAME=$(driver))