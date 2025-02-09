COMPILER = g++

MODULE_NAME = mod1

TARGET_DIR = ../../bins
TARGET_NAME = mod1_bin
TARGET = $(TARGET_DIR)/$(TARGET_NAME)

OBJ_DIR = ../../objs
OBJ = $(OBJ_DIR)/$(MODULE_NAME).o

CFLAGS = -Wall -Werror -Wextra -c
LDFLAGS = -lm

$(TARGET) : $(OBJ)
	$(COMPILER) $< -o $@ $(LDFLAGS)

$(OBJ) : $(MODULE_NAME).cpp
	$(COMPILER) $(CFLAGS) $< -o $@


clean : 
	-rm -rf $(TARGET) $(OBJ)
