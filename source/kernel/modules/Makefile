MODULES=hello_world

export MODULE_LD_SCRIPT=$(CURDIR)/module.ld
export CFLAGS64+=-fPIC -fno-plt -fno-pic

.PHONY: all
all:
	$(foreach module, $(MODULES), cd $(module) && $(MAKE) MODULE_NAME=$(module))