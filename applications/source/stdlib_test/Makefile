SRC_DIR=src

OBJS+=$(OBJ_DIR)/main.o
# OBJS+=$(OBJ_DIR)/dirent.o

HEADERS=$(shell find $(INCLUDE_DIR) -name "*.h")

.PHONY: all
all: $(BIN_DIR)/stdlib_test

.PHONY: clean
clean:

$(BIN_DIR)/stdlib_test: $(OBJS)
	mkdir -p $(@D)
	$(CC) $(CFLAGS) $(OBJS) -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEADERS)
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -Iinclude -c $< -o $@

