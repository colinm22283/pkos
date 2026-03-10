SRC_DIR=src

OBJS+=$(OBJ_DIR)/main.o

HEADERS=$(shell find $(INCLUDE_DIR) -name "*.h")

.PHONY: all
all: $(BIN_DIR)/heapstat

.PHONY: clean
clean:

$(BIN_DIR)/heapstat: $(OBJS)
	mkdir -p $(@D)
	$(CC) $(CFLAGS) $(OBJS) -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEADERS)
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

