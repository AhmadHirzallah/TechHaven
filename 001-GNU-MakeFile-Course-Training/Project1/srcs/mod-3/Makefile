MODULE_NAME = mod3

COMPILER = g++

TARGET_DIR = ../../bins
TARGET_NAME = mod3_bin
TARGET = $(TARGET_DIR)/$(TARGET_NAME) 

OBJ_DIR = ../../objs
OBJ = $(OBJ_DIR)/$(MODULE_NAME).o

INCLUDE_PATH = ../../share_headers
WARN_FLAGS = -Wall -Werror -Wextra
CFLAG = $(WARN_FLAGS) -I$(INCLUDE_PATH) 

LIBS_PATH = ../../libs
LD_FLAGS = -L$(LIBS_PATH) -lmod2		# Using the Dynamic Library using -lmod2

$(TARGET) : $(OBJ)
	$(COMPILER) $< -o $@ $(LD_FLAGS) -Wl,-rpath,$(LIBS_PATH)

$(OBJ) : $(MODULE_NAME).cpp
	$(COMPILER) $(CFLAG) -c $< -o $@

clean:
	-rm $(TARGET) $(OBJ) 

.PHONY : clean
