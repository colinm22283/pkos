HEADERS=$(wildcard include/*.h)

OBJS=main.o page_stack.o write.o parse.o
OBJ_DIRS=$(foreach OBJ, $(OBJS), build/obj/$(OBJ))

CC=gcc
CFLAGS=-O2 -c

LD=ld
LDFLAGS=-lc

.PHONY: all
all: build/mkfs

.PHONY: clean
clean:
	rm -rf build/*

build/mkfs: $(OBJ_DIRS)
	$(CC) $(LDFLAGS) $(OBJ_DIRS) -o $@

build/obj/%.o: src/%.c $(HEADERS)
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -I include $< -o $@