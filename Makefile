INC_DIR = include
SRC_DIR = src
OBJ_DIR = obj
CTRL_DIR = ctrl_programs
CTRL_OBJ_DIR = ctrl_obj

ALT_DEVICE_FAMILY ?= soc_cv_av

SOCEDS_DEST_ROOT ?= ${HOME}/intelFPGA/20.1/embedded

COMPILER_PATH ?= ${SOCEDS_DEST_ROOT}/host_tools/arm_toolchains/arm/bin
ALTERA_IP_ROOT ?= ${HOME}/intelFPGA/20.1/ip/altera/sopc_builder_ip
HWLIBS_ROOT ?= $(SOCEDS_DEST_ROOT)/ip/altera/hps/altera_hps/hwlib

ALTERA_INC_DIR ?= /home/bl4z3/intelFPGA/20.1/ip/altera/
SOPC_BUILDER_IP_DIR ?= /home/bl4z3/intelFPGA/20.1/ip/altera/sopc_builder_ip/

BASE_INC_DIR := $(wildcard $(SOPC_BUILDER_IP_DIR)*/inc)
HAL_INC_DIR := $(wildcard $(SOPC_BUILDER_IP_DIR)*/*/inc)
INC_DIR := $(wildcard $(ALTERA_INC_DIR)*/*/HAL/inc)
PREFIX_INC := $(addprefix -I,$(BASE_INC_DIR)) # $(addprefix -I,$(HAL_INC_DIR)) # $(addprefix -I,$(INC_DIR))

CROSS_COMPILE = arm-none-linux-gnueabihf-
CXX_FLAGS = -std=c++17 -O3 -g -Wall -D$(ALT_DEVICE_FAMILY) -I$(HWLIBS_ROOT)/include/$(ALT_DEVICE_FAMILY) -I$(HWLIBS_ROOT)/include -Iinclude $(PREFIX_INC)
LD_FLAGS = -g -Wall

CXX = $(COMPILER_PATH)/$(CROSS_COMPILE)g++

SRC_FILES := $(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC_FILES))

TEST_SRC_FILES := $(wildcard $(CTRL_DIR)/*.cpp)
TEST_OBJ_FILES := $(patsubst $(CTRL_DIR)/%.cpp,$(CTRL_OBJ_DIR)/%.o,$(TEST_SRC_FILES))
TEST_EXE_FILES := $(patsubst $(CTRL_DIR)/%.cpp,$(CTRL_OBJ_DIR)/%,$(TEST_SRC_FILES))

build_test: $(OBJ_FILES) $(TEST_OBJ_FILES) $(TEST_EXE_FILES)

$(TEST_EXE_FILES): $(OBJ_FILES) $(TEST_OBJ_FILES)
	$(CXX) $(LD_FLAGS) $^ -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXX_FLAGS) -c -o $@ $<

$(CTRL_OBJ_DIR)/%.o: $(CTRL_DIR)/%.cpp
	$(CXX) $(CXX_FLAGS) -c -o $@ $<

clean:
	rm -f $(TARGET) $(OBJ_DIR)/*.o