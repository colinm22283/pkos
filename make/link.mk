$(BUILD_DIR)/pkos.bin: $(LDSCRIPTS) $(OBJECTS)
	$(LD) $(LDFLAGS) $(OBJECTS) -o $@