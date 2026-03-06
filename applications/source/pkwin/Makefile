SRC_DIR=src
INCLUDE_DIR=include

OBJS+=$(OBJ_DIR)/main.o
OBJS+=$(OBJ_DIR)/packet.o

HEADERS=$(shell find $(INCLUDE_DIR) -name "*.h")

.PHONY: all
all: $(BIN_DIR)/pkwin

.PHONY: clean
clean:

$(BIN_DIR)/pkwin: $(OBJS)
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) $(OBJS) -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEADERS)
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

