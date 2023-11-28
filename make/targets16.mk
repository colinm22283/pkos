$(OBJ_DIR)/%.o: $(SOURCE_DIR)/%.c
	mkdir -p $(@D)
	$(CC16) $(CFLAGS16) $< -o $@

$(OBJ_DIR)/%.o: $(SOURCE_DIR)/%.cpp
	mkdir -p $(@D)
	$(CXX16) $(CXXFLAGS16) $< -o $@

$(OBJ_DIR)/%.o: $(SOURCE_DIR)/%.s
	mkdir -p $(@D)
	$(ASM) $(ASMFLAGS) $< -o $@