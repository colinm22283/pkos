SRC_DIR=src
INCLUDE_DIR=include

OBJS+=$(OBJ_DIR)/main.o
OBJS+=$(OBJ_DIR)/packet.o
OBJS+=$(OBJ_DIR)/bmp.o

HEADERS=$(shell find $(INCLUDE_DIR) -name "*.h")

.PHONY: all
all: $(BIN_DIR)/pkwpaint

.PHONY: clean
clean:

$(BIN_DIR)/pkwpaint: $(OBJS)
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) $(OBJS) -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEADERS)
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) -c $< -o $@
