INC_DIR = include
SRC_DIR = src
OBJ_DIR = obj
TARGET = soc_sys

ALT_DEVICE_FAMILY ?= soc_cv_av
COMPILER_PATH ?= ${HOME}/intelFPGA/20.1/embedded/host_tools/linaro/gcc/bin/
SOCEDS_DEST_ROOT ?= ${HOME}/intelFPGA/20.1/embedded

CROSS_COMPILE = arm-none-linux-gnueabihf-
HWLIBS_ROOT = $(SOCEDS_DEST_ROOT)/ip/altera/hps/altera_hps/hwlib
CXX_FLAGS = -g -Wall -D$(ALT_DEVICE_FAMILY) -I$(HWLIBS_ROOT)/include/$(ALT_DEVICE_FAMILY) -I$(HWLIBS_ROOT)/include -Iinclude
LD_FLAGS = -g -Wall

CXX = $(COMPILER_PATH)$(CROSS_COMPILE)g++

SRC_FILES := $(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC_FILES))

build: $(TARGET)

$(TARGET): $(OBJ_FILES)
	$(CXX) $(LD_FLAGS) $^ -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXX_FLAGS) -c -o $@ $<

clean:
	rm -f $(TARGET) $(OBJ_DIR)/*.o