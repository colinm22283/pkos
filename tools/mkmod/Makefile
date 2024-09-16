HEADERS=$(wildcard include/*.h)

OBJS=main.o obj_parser.o
OBJ_DIRS=$(foreach OBJ, $(OBJS), build/obj/$(OBJ))

CC=gcc
CFLAGS=-O0 -g -c

LD=ld
LDFLAGS=-lc

.PHONY: all
all: build/mkmod

.PHONY: clean
clean:
	rm -rf build/*

build/mkmod: $(OBJ_DIRS)
	$(CC) $(LDFLAGS) $(OBJ_DIRS) -o $@

build/obj/%.o: src/%.c $(HEADERS)
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -I include $< -o $@