BUILD_DIR=build
OBJ_DIR=$(BUILD_DIR)/obj
SOURCE_DIR=src
EXE_DIR?=$(BUILD_DIR)

EXE_BIN?=$(EXE_DIR)/sh

INCLUDE_DIRS+=include

OBJS+=$(OBJ_DIR)/entry.o
OBJS+=$(OBJ_DIR)/main.o

.PHONY: all
all: $(EXE_BIN)

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR)

$(EXE_BIN): $(OBJS)
	mkdir -p $(@D)
	$(LD) $(LDFLAGS) $(OBJS) -o $@

INCLUDE_PARAMS=$(foreach d, $(INCLUDE_DIRS) $(AUTOGEN_INCLUDE_DIRS), -I$d)
CHEADERS=$(foreach d, $(INCLUDE_DIRS), $(shell find $d -type f -name '*.h'))

$(OBJ_DIR)/%.o: $(SOURCE_DIR)/%.c $(CHEADERS)
	mkdir -p $(@D)
	$(CC) $(CFLAGS) $(INCLUDE_PARAMS) $< -o $@

$(OBJ_DIR)/%.o: $(SOURCE_DIR)/%.s $(CHEADERS)
	mkdir -p $(@D)
	$(AS) $(ASFLAGS) $< -o $@
