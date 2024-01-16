INCLUDE_PARAMS=$(foreach d, $(INCLUDE_DIRS), -I$d)
CHEADERS=$(foreach d, $(INCLUDE_DIRS), $(shell find $d -type f -name '*.h'))
CXXHEADERS=$(foreach d, $(INCLUDE_DIRS), $(shell find $d -type f -name '*.hpp'))

$(OBJ_DIR)/16/%.o: $(SOURCE_DIR)/%.c $(CHEADERS)
	mkdir -p $(@D)
	$(CC16) $(CFLAGS16) $(INCLUDE_PARAMS) $< -o $@

$(OBJ_DIR)/16/%.o: $(SOURCE_DIR)/%.cpp $(CHEADERS) $(CXXHEADERS)
	mkdir -p $(@D)
	$(CXX16) $(CXXFLAGS16) $(INCLUDE_PARAMS) $< -o $@

$(OBJ_DIR)/16/%.o: $(SOURCE_DIR)/%.s
	mkdir -p $(@D)
	$(ASM16) $(ASMFLAGS) $< -o $@