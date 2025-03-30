MODULE_NAME = mod4

TARGET_DIR = ../../libs
TARGET_NAME = lib$(MODULE_NAME).a
TARGET = $(TARGET_DIR)/$(TARGET_NAME)

OBJ_DIR = ../../objs
OBJ = $(OBJ_DIR)/$(MODULE_NAME).o

COMPILER = g++
WARN_FLAGS = -Wall -Wextra -Werror 
INCLUDE_FLAG = -I../../share_headers
CFLAGS = $(WARN_FLAGS) -fPIC $(INCLUDE_FLAG) 

LD_FLAGS = -L$(TARGET_DIR) -l$(MODULE_NAME)

TEST_MODULE = test$(MODULE_NAME).cpp 
TEST_BIN_DIR = ../../test_bins
TEST_OBJ = $(TEST_BIN_DIR)/test$(MODULE_NAME).o
TEST = $(TEST_BIN_DIR)/test$(MODULE_NAME)

$(TARGET) : $(OBJ)
	ar rcs $@ $^

$(OBJ) : $(MODULE_NAME).cpp
	$(COMPILER) $(CFLAGS) -c $< -o $@

$(CREATE_TEST_BIN_DIR) :
	mkdir -p $(TEST_BIN_DIR)

$(TEST) : $(TEST_OBJ) | $(CREATE_TEST_BIN_DIR) 
	$(COMPILER) $< -o $@ $(LD_FLAGS)

$(TEST_OBJ) : $(TEST_MODULE)
	$(COMPILER) $(CFLAGS) -c $< -o $@

clean : 
	-rm -rf $(TARGET) $(OBJ) $(TEST)

test : $(TEST)

.PHONY: clean test

