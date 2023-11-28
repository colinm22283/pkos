$(BUILD_DIR)/pkos.bin: $(LDSCRIPT) bootloader kernel
	$(LD) $(LDFLAGS) $(OBJECTS) -o $@