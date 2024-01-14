KN_OBJ_DIR=$(OBJ_DIR)/64/kernel/src
KN_OBJS=$(KN_OBJ_DIR)/entry.o $(KN_OBJ_DIR)/bios_console.o
KN_SOURCE_DIR=$(SOURCE_DIR)/kernel

# string
KN_OBJS+=$(KN_OBJ_DIR)/string/strcpy.o
KN_OBJS+=$(KN_OBJ_DIR)/string/strcmp.o

# memory
KN_OBJS+=$(KN_OBJ_DIR)/memory/memcpy.o

# memory manager
KN_OBJS+=$(KN_OBJ_DIR)/memory_manager/mm_init.o

# paging
KN_OBJS+=$(KN_OBJ_DIR)/paging/paging.o

# interrupt
KN_OBJS+=$(KN_OBJ_DIR)/interrupt/pic.o
KN_OBJS+=$(KN_OBJ_DIR)/interrupt/init.o
KN_OBJS+=$(KN_OBJ_DIR)/idt.o

# all of the interrupt handlers
KN_OBJS+=$(KN_OBJ_DIR)/interrupt/handlers/irq/null_pic_handler.o
KN_OBJS+=$(KN_OBJ_DIR)/interrupt/handlers/irq/null_pic_handler_entry.o

KN_OBJS+=$(KN_OBJ_DIR)/interrupt/handlers/internal/unimp_handler.o
KN_OBJS+=$(KN_OBJ_DIR)/interrupt/handlers/internal/unimp_handler_entry.o

KN_OBJS+=$(KN_OBJ_DIR)/interrupt/handlers/internal/system_handler.o
KN_OBJS+=$(KN_OBJ_DIR)/interrupt/handlers/internal/system_handler_entry.o

KN_OBJS+=$(KN_OBJ_DIR)/interrupt/handlers/internal/gpf_handler.o
KN_OBJS+=$(KN_OBJ_DIR)/interrupt/handlers/internal/gpf_handler_entry.o

KN_OBJS+=$(KN_OBJ_DIR)/interrupt/handlers/internal/page_fault_handler.o
KN_OBJS+=$(KN_OBJ_DIR)/interrupt/handlers/internal/page_fault_handler_entry.o

KN_OBJS+=$(KN_OBJ_DIR)/interrupt/handlers/internal/keyboard_handler.o
KN_OBJS+=$(KN_OBJ_DIR)/interrupt/handlers/internal/keyboard_handler_entry.o

INCLUDE_DIRS+=source/kernel/include

$(BIN_DIR)/kernel.bin: $(KN_OBJS) $(KN_SOURCE_DIR)/kernel.ld
	mkdir -p $(BIN_DIR)
	$(LD64) $(LDFLAGS) -T$(KN_SOURCE_DIR)/kernel.ld $(KN_OBJS) -o $@
	truncate $@ -s 64000