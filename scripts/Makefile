APPLICATION_NAMES=init

SYM_FILES=$(foreach a, $(APPLICATION_NAMES), ../build/fsroot/bin/$a)
SRC_DIRS=$(foreach a, $(APPLICATION_NAMES), ../applications/source/$a/)

GDB_ARGS+=$(foreach s, $(SYM_FILES), -ex "add-symbol-file $s")
GDB_ARGS+=$(foreach s, $(SRC_DIRS), -ex "directory $s")
GDB_ARGS+=-ex "directory $(shell x86_64-pkos-gcc -print-sysroot)"

KERNEL_ARGS=-ex "add-symbol-file ../pkernel/build/bin/kernel.sym"

.PHONY: all
all: stdlib.gdb
	x86_64-elf-gdb -x base.gdb -x stdlib.gdb $(GDB_ARGS) $(KERNEL_ARGS)

.PHONY: user
user:
	x86_64-elf-gdb -x base.gdb -x stdlib.gdb $(GDB_ARGS)

stdlib.gdb:
	echo "directory ../../pkos_toolchain/pkos_stdlib/libc" > $@

