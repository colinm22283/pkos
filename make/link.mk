$(BUILD_DIR)/pkos.bin: $(LDSCRIPTS) bootloader kernel
	$(LD) $(LDFLAGS) $(OBJECTS) -o $@