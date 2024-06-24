MODULES=hello_world

export MODULE_LD_SCRIPT=$(CURDIR)/module.ld
export CFLAGS+=-fPIC

.PHONY: all
all:
	$(foreach module, $(MODULES), cd $(module) && $(MAKE) MODULE_NAME=$(module))