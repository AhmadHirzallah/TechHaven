COMPILER = g++

MODULE_NAME = mod2

TARGET_DIR = ../../libs
TARGET_NAME = lib$(MODULE_NAME).so
TARGET = $(TARGET_DIR)/$(TARGET_NAME)

OBJ_DIR = ../../objs
OBJ2 = $(OBJ_DIR)/$(MODULE_NAME).o

TEST_MODULE = test_mod2.cpp
TEST_BIN_DIR = ../../test_bins
TEST_OBJ = $(TEST_BIN_DIR)/test$(MODULE_NAME).o
TEST = $(TEST_BIN_DIR)/test$(MODULE_NAME)


WARN_FLAGS = -Wall -Wextra -Werror
INC_PATH = ../../share_headers
CFLAGS = $(WARN_FLAGS) -fPIC -I$(INC_PATH) -c

# If we used it when it is empty (nothing after =) it is possible because it don't do anything because it is empty ! :)
LDFLAGS =  -L$(TARGET_DIR) -l$(MODULE_NAME)

#SHARED_LIB_ERR_FIX: -Wl,-rpath,$(TARGET_DIR)

$(TARGET) : $(OBJ2)
	$(COMPILER) -shared $< -o $@

$(OBJ2) : $(MODULE_NAME).cpp
	$(COMPILER) $(CFLAGS) $< -o $@

$(TEST_BIN_DIR):
	mkdir -p $(TEST_BIN_DIR)

$(TEST) : $(TEST_OBJ)
	$(COMPILER) $(<) -o $(@) $(LDFLAGS) -Wl,-rpath,$(TARGET_DIR)

$(TEST_OBJ) : $(TEST_MODULE) | $(TEST_BIN_DIR)
	$(COMPILER) $(CFLAGS)  $(<) -o $(@)
       

clean:
	-rm  -rf $(TARGET) $(OBJ2) $(TEST_BIN_DIR)

test : $(TEST)

.PHONY: test clean

