DRIVERS=disc_pio

export DRIVER_LD_SCRIPT=$(CURDIR)/driver.ld
export CFLAGS+=-fPIC

.PHONY: all
all:
	$(foreach driver, $(DRIVERS), cd $(driver) && $(MAKE) DRIVER_NAME=$(driver))