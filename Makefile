INC_DIR = include
SRC_DIR = src
TARGET = soc_sys

ALT_DEVICE_FAMILY ?= soc_cv_av
HWLIBS_ROOT = $(SOCEDS_DEST_ROOT)/ip/altera/hps/altera_hps/hwlib
CXX_FLAGS = -g -Wall -D$(ALT_DEVICE_FAMILY) -I$(HWLIBS_ROOT)/include/$(ALT_DEVICE_FAMILY) -I$(HWLIBS_ROOT)/include -Iinclude
LD_FLAGS = -g -Wall

CXX = ${CROSS_COMPILE}g++

build: clean $(TARGET)

$(TARGET): main.o
	$(CXX) $(LD_FLAGS) $^ -o $@

%.o : $(SRC_DIR)/%.cpp
	$(CXX) $(CXX_FLAGS) -c $< -o $@

clean:
	rm -f $(TARGET) *.a *.o *~