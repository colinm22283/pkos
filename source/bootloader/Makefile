BL_SOURCE_DIR=$(SOURCE_DIR)/bootloader
BL_OD_32=$(OBJ_DIR)/32/bootloader/src
BL_OD_64=$(OBJ_DIR)/64/bootloader/src

INCLUDE_DIRS+=$(CURDIR)/include

OBJS+=$(BL_OD_32)/bootloader_entry.o

OBJS+=$(BL_OD_32)/interrupt/idt.o
OBJS+=$(BL_OD_32)/interrupt/init.o

OBJS+=$(BL_OD_32)/interrupt/null_handler.o
OBJS+=$(BL_OD_32)/interrupt/fatal_handler.o
OBJS+=$(BL_OD_32)/interrupt/null_pic_handler_entry.o
OBJS+=$(BL_OD_32)/interrupt/null_pic_handler.o
OBJS+=$(BL_OD_32)/interrupt/keyboard_handler_entry.o
OBJS+=$(BL_OD_32)/interrupt/keyboard_handler.o
OBJS+=$(BL_OD_32)/interrupt/keyboard_lut.o

OBJS+=$(BL_OD_32)/pic/remap.o
OBJS+=$(BL_OD_32)/pic/mask.o

#OBJS+=$(BL_OD_64)/gdt64.o
#OBJS+=$(BL_OD_64)/page_tables.o

OBJS+=$(BL_OD_32)/boot_error.o

OBJS+=$(BL_OD_32)/console/console.o
OBJS+=$(BL_OD_32)/console/newline.o
OBJS+=$(BL_OD_32)/console/print.o
OBJS+=$(BL_OD_32)/console/print_color.o
OBJS+=$(BL_OD_32)/console/print_hex.o
OBJS+=$(BL_OD_32)/console/put.o
OBJS+=$(BL_OD_32)/console/backspace.o

OBJS+=$(BL_OD_32)/shell/shell_entry.o
OBJS+=$(BL_OD_32)/shell/keyboard_handler.o
OBJS+=$(BL_OD_32)/shell/input.o
OBJS+=$(BL_OD_32)/shell/command_tree.o
OBJS+=$(BL_OD_32)/shell/execute.o

OBJS+=$(BL_OD_32)/commands/echo.o
OBJS+=$(BL_OD_32)/commands/exit.o
OBJS+=$(BL_OD_32)/commands/boot.o

include $(MAKE_SCRIPTS)

$(BIN_DIR)/bootloader.bin: $(OBJS) $(BL_SOURCE_DIR)/bootloader.ld
	mkdir -p $(BIN_DIR)
	$(LD32) $(LDFLAGS) -T$(BL_SOURCE_DIR)/bootloader.ld $(OBJS) -o $@
	truncate $@ -s 4096