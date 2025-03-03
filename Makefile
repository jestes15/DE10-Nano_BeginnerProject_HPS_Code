INC_DIR = include
SRC_DIR = src
OBJ_DIR = obj
CTRL_DIR = ctrl_programs
CTRL_OBJ_DIR = ctrl_obj
CTRL_EXEC = executables

ALT_DEVICE_FAMILY ?= soc_cv_av
SOCEDS_DEST_ROOT ?= ${HOME}/intelFPGA/20.1

COMPILER_PATH ?= $(SOCEDS_DEST_ROOT)/embedded/host_tools/arm_toolchains/aarch32/bin
NIOS2_EDS_COMP ?= $(SOCEDS_DEST_ROOT)/nios2eds/components
ALTERA_IP ?= $(SOCEDS_DEST_ROOT)/embedded/ip/altera
SOPC_BUILDER_IP ?= $(ALTERA_IP)/sopc_builder_ip
UNI_PROG_IP_AV ?= $(ALTERA_IP)/university_program/audio_video
UNI_PROG_IP_IO ?= $(ALTERA_IP)/university_program/input_output
UNI_PROG_IP ?= $(ALTERA_IP)/university_program
PGM_IP ?= $(ALTERA_IP)/pgm


INCDIR = $(ALTERA_IP)/hps/altera_hps/hwlib/include \
		$(ALTERA_IP)/hps/altera_hps/hwlib/include/$(ALT_DEVICE_FAMILY) \
		include

CROSS_COMPILE = arm-none-linux-gnueabihf-
CXX_FLAGS = -std=c++17 -O3 -g -Wall -D$(ALT_DEVICE_FAMILY) $(addprefix -I,$(INCDIR))
LD_FLAGS = -g -Wall

CXX = $(COMPILER_PATH)/$(CROSS_COMPILE)g++
CC = $(COMPILER_PATH)/$(CROSS_COMPILE)g++

SRC_FILES := $(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC_FILES))

TEST_SRC_FILES := $(wildcard $(CTRL_DIR)/*.cpp)
TEST_OBJ_FILES := $(patsubst $(CTRL_DIR)/%.cpp,$(CTRL_OBJ_DIR)/%.o,$(TEST_SRC_FILES))
TEST_EXE_FILES := $(patsubst $(CTRL_DIR)/%.cpp,$(CTRL_EXEC)/%,$(TEST_SRC_FILES))

build: $(OBJ_FILES) $(TEST_OBJ_FILES) $(TEST_EXE_FILES)

# Rule to build object files from src
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXX_FLAGS) -c -o $@ $<

# Rule to build object files from tests (CTRL_DIR)
$(CTRL_OBJ_DIR)/%.o: $(CTRL_DIR)/%.cpp $(OBJ_FILES)
	@mkdir -p $(@D)
	$(CXX) $(CXX_FLAGS) -c -o $@ $<

# Rule to link test executables, linking with all object files from src
$(CTRL_EXEC)/%: $(CTRL_OBJ_DIR)/%.o $(OBJ_FILES)
	@mkdir -p $(@D)
	$(CXX) $(LD_FLAGS) $^ -o $@

.PHONY: clean
clean:
	rm -f $(OBJ_DIR)/*.o $(CTRL_OBJ_DIR)/*.o $(CTRL_OBJ_DIR)/* $(CTRL_EXEC)/*