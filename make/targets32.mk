INCLUDE_PARAMS=$(foreach d, $(INCLUDE_DIRS), -I$d)

$(OBJ_DIR)/%.o: $(SOURCE_DIR)/%.c
	mkdir -p $(@D)
	$(CC32) $(CFLAGS32) $(INCLUDE_PARAMS) $< -o $@

$(OBJ_DIR)/%.o: $(SOURCE_DIR)/%.cpp
	mkdir -p $(@D)
	$(CXX32) $(CXXFLAGS32) $(INCLUDE_PARAMS) $< -o $@

$(OBJ_DIR)/%.o: $(SOURCE_DIR)/%.s
	mkdir -p $(@D)
	$(ASM) $(ASMFLAGS) $< -o $@