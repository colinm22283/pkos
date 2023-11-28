$(OBJ_DIR)/%.o: $(SOURCE_DIR)/%.c
	mkdir -p $(@D)
	$(CC32) $(CFLAGS32) $< -o $@

$(OBJ_DIR)/%.o: $(SOURCE_DIR)/%.cpp
	mkdir -p $(@D)
	$(CXX32) $(CXXFLAGS32) $< -o $@

$(OBJ_DIR)/%.o: $(SOURCE_DIR)/%.s
	mkdir -p $(@D)
	$(ASM) $(ASMFLAGS) $< -o $@