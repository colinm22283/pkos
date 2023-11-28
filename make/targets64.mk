INCLUDE_PARAMS=$(foreach d, $(INCLUDE_DIRS), -I$d)
CHEADERS=$(foreach d, $(INCLUDE_DIRS), $(shell find $d -type f -name '*.h'))
CXXHEADERS=$(foreach d, $(INCLUDE_DIRS), $(shell find $d -type f -name '*.hpp'))

$(OBJ_DIR)/64/%.o: $(SOURCE_DIR)/%.c $(CHEADERS)
	echo "ERROR NOT IMPLEMENTED"
	mkdir -p $(@D)
	$(CC64) $(CFLAGS64) $(INCLUDE_PARAMS) $< -o $@

$(OBJ_DIR)/64/%.o: $(SOURCE_DIR)/%.cpp $(CHEADERS) $(CXXHEADERS)
	echo "ERROR NOT IMPLEMENTED"
	mkdir -p $(@D)
	$(CXX64) $(CXXFLAGS64) $(INCLUDE_PARAMS) $< -o $@