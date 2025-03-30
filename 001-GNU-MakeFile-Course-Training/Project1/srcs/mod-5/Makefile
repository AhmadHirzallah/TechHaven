MODULE_NAME = mod5

TARGET_DIR = ../../bins
TARGET_NAME = mod5_bin
TARGET = $(TARGET_DIR)/$(TARGET_NAME)

OBJ_DIR = ../../objs
OBJ = $(OBJ_DIR)/$(MODULE_NAME).o

COMPILER = g++
WARN_FLAGS = -Wall -Werror -Wextra
INC_FLAGS = -I../../share_headers
C_FLAGS = $(WARN_FLAGS)  $(INC_FLAGS)

LD_FLAGS = -L../../libs -lmod2 -lmod4

$(TARGET) : $(OBJ)
	$(COMPILER) $< -o $@ $(LD_FLAGS) -Wl,-rpath,../../libs

$(OBJ) : $(MODULE_NAME).cpp 
	$(COMPILER) $(C_FLAGS) -c $< -o $@ 

clean : 
	-rm -rf $(TARGET) $(OBJ)
