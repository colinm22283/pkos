INCLUDE_PARAMS=$(foreach d, $(INCLUDE_DIRS), -I$d)

$(OBJ_DIR)/%.o: $(SOURCE_DIR)/%.c
	mkdir -p $(@D)
	$(CC16) $(CFLAGS16) $(INCLUDE_PARAMS) $< -o $@

$(OBJ_DIR)/%.o: $(SOURCE_DIR)/%.cpp
	mkdir -p $(@D)
	$(CXX16) $(CXXFLAGS16) $(INCLUDE_PARAMS) $< -o $@

$(OBJ_DIR)/%.o: $(SOURCE_DIR)/%.s
	mkdir -p $(@D)
	$(ASM) $(ASMFLAGS) $< -o $@