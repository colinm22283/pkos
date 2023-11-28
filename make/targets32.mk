INCLUDE_PARAMS=$(foreach d, $(INCLUDE_DIRS), -I$d)
CHEADERS=$(foreach d, $(INCLUDE_DIRS), $(shell find $d -type f -name '*.h'))
CXXHEADERS=$(foreach d, $(INCLUDE_DIRS), $(shell find $d -type f -name '*.hpp'))

$(OBJ_DIR)/32/%.o: $(SOURCE_DIR)/%.c $(CHEADERS)
	mkdir -p $(@D)
	$(CC32) $(CFLAGS32) $(INCLUDE_PARAMS) $< -o $@

$(OBJ_DIR)/32/%.o: $(SOURCE_DIR)/%.cpp $(CHEADERS) $(CXXHEADERS)
	mkdir -p $(@D)
	$(CXX32) $(CXXFLAGS32) $(INCLUDE_PARAMS) $< -o $@