BUILD_DIR=build
OBJ_DIR=$(BUILD_DIR)/obj
SOURCE_DIR=src
EXE_DIR?=$(BUILD_DIR)

EXE_BIN?=$(EXE_DIR)/nn

override INCLUDE_DIRS+=$(CURDIR)/include

INCLUDE_PARAMS=$(foreach d, $(INCLUDE_DIRS) $(AUTOGEN_INCLUDE_DIRS), -I$d)
CHEADERS=$(foreach d, $(INCLUDE_DIRS), $(shell find $d -type f -name '*.h'))

OBJS+=$(OBJ_DIR)/entry.o
OBJS+=$(OBJ_DIR)/heap.o

OBJS+=$(OBJ_DIR)/network.o
OBJS+=$(OBJ_DIR)/layer.o
OBJS+=$(OBJ_DIR)/config.o

OBJS+=$(OBJ_DIR)/main.o
OBJS+=$(OBJ_DIR)/graph.o
OBJS+=$(OBJ_DIR)/hw.o

.PHONY: all
all: $(EXE_BIN)

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR)

$(EXE_BIN): $(OBJS)
	mkdir -p $(@D)
	$(LD) $(LDFLAGS) $(OBJS) -o $@

$(OBJ_DIR)/%.o: $(SOURCE_DIR)/%.c $(CHEADERS)
	echo $(INCLUDE_DIRS)
	echo $(INCLUDE_PARAMS)
	mkdir -p $(@D)
	$(CC) $(CFLAGS) $(INCLUDE_PARAMS) $< -o $@

$(OBJ_DIR)/%.o: $(SOURCE_DIR)/%.s $(CHEADERS)
	mkdir -p $(@D)
	$(AS) $(ASFLAGS) $< -o $@

