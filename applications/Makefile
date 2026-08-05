export BUILD_DIR=$(CURDIR)/build
export BIN_DIR=$(BUILD_DIR)/bin

export CC=x86_64-pkos-gcc

export override CFLAGS=-O0

PROGS+=pksh
PROGS+=pkwin
PROGS+=pkwball
PROGS+=heapstat
PROGS+=empty
PROGS+=init

TARGETS=$(foreach p, $(PROGS), build-$p)

.PHONY: all
all: $(TARGETS)

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR)

.PHONY: build-%
build-%:
	cd source/$* && $(MAKE) \
		OBJ_DIR=$(BUILD_DIR)/obj/$* \
		SRC_DIR=$(CURDIR)/source/$*/src \
		INCLUDE_DIR=$(CURDIR)/source/$*/include

