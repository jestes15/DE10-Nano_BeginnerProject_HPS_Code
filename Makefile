INC_DIR = include
SRC_DIR = src
OBJ_DIR = obj
CTRL_DIR = ctrl_programs
CTRL_OBJ_DIR = ctrl_obj
CTRL_EXEC = executables

ALT_DEVICE_FAMILY ?= soc_cv_av
SOCEDS_DEST_ROOT ?= ${HOME}/Intel_SoC_FPGFA_DevTools/SoCEDS/20.1

COMPILER_PATH ?= $(SOCEDS_DEST_ROOT)/embedded/host_tools/arm_toolchains/aarch32/bin
NIOS2_EDS_COMP ?= $(SOCEDS_DEST_ROOT)/nios2eds/components
ALTERA_IP ?= $(SOCEDS_DEST_ROOT)/embedded/ip/altera
SOPC_BUILDER_IP ?= $(ALTERA_IP)/sopc_builder_ip
UNI_PROG_IP_AV ?= $(ALTERA_IP)/university_program/audio_video
UNI_PROG_IP_IO ?= $(ALTERA_IP)/university_program/input_output
UNI_PROG_IP ?= $(ALTERA_IP)/university_program
PGM_IP ?= $(ALTERA_IP)/pgm


INCDIR = $(NIOS2_EDS_COMP)/altera_ro_zipfs/HAL/inc \
		$(NIOS2_EDS_COMP)/altera_hal/HAL/inc \
		$(NIOS2_EDS_COMP)/altera_nios2_gen2/HAL/inc \
		$(NIOS2_EDS_COMP)/altera_nios2_gen2/UCOSIII/inc \
		$(NIOS2_EDS_COMP)/altera_nios2_gen2/UCOSII/inc \
		$(NIOS2_EDS_COMP)/altera_hostfs/HAL/inc \
		$(NIOS2_EDS_COMP)/micrium_uc_osii/UCOSII/inc \
		$(NIOS2_EDS_COMP)/altera_nios2/HAL/inc \
		$(NIOS2_EDS_COMP)/altera_nios2/UCOSII/inc \
		$(NIOS2_EDS_COMP)/altera_iniche/UCOSII/inc \
		$(NIOS2_EDS_COMP)/altera_quad_seven_seg/HAL/inc \
		$(ALTERA_IP)/altera_msgdma/top/HAL/inc \
		$(ALTERA_IP)/altera_msgdma/top/inc \
		$(ALTERA_IP)/altera_avalon_mailbox/HAL/inc \
		$(ALTERA_IP)/altera_avalon_mailbox/inc \
		$(ALTERA_IP)/generic_qspi_controller/HAL/inc \
		$(ALTERA_IP)/generic_qspi_controller/inc \
		$(ALTERA_IP)/altera_modular_adc/top/HAL/inc \
		$(ALTERA_IP)/altera_modular_adc/top/inc \
		$(ALTERA_IP)/altera_16550_uart/HAL/inc \
		$(ALTERA_IP)/altera_16550_uart/inc \
		$(SOPC_BUILDER_IP)/altera_avalon_sysid/HAL/inc \
		$(SOPC_BUILDER_IP)/altera_avalon_sysid/inc \
		$(SOPC_BUILDER_IP)/altera_avalon_mutex/HAL/inc \
		$(SOPC_BUILDER_IP)/altera_avalon_mutex/inc \
		$(SOPC_BUILDER_IP)/altera_avalon_mutex/LWHAL/inc \
		$(SOPC_BUILDER_IP)/altera_avalon_epcs_flash_controller/HAL/inc \
		$(SOPC_BUILDER_IP)/altera_avalon_epcs_flash_controller/inc \
		$(SOPC_BUILDER_IP)/altera_avalon_fifo/HAL/inc \
		$(SOPC_BUILDER_IP)/altera_avalon_fifo/inc \
		$(SOPC_BUILDER_IP)/altera_avalon_data_sink/HAL/inc \
		$(SOPC_BUILDER_IP)/altera_avalon_data_sink/inc \
		$(SOPC_BUILDER_IP)/altera_avalon_spi/HAL/inc \
		$(SOPC_BUILDER_IP)/altera_avalon_spi/inc \
		$(SOPC_BUILDER_IP)/altera_avalon_cf/HAL/inc \
		$(SOPC_BUILDER_IP)/altera_avalon_cf/inc \
		$(SOPC_BUILDER_IP)/altera_avalon_timer/HAL/inc \
		$(SOPC_BUILDER_IP)/altera_avalon_timer/inc \
		$(SOPC_BUILDER_IP)/altera_avalon_cfi_flash/HAL/inc \
		$(SOPC_BUILDER_IP)/altera_avalon_spislave_to_avalonmm_bridge/HAL/inc \
		$(SOPC_BUILDER_IP)/altera_avalon_spislave_to_avalonmm_bridge/inc \
		$(SOPC_BUILDER_IP)/altera_avalon_pio/inc \
		$(SOPC_BUILDER_IP)/altera_avalon_data_source/HAL/inc \
		$(SOPC_BUILDER_IP)/altera_avalon_data_source/inc \
		$(SOPC_BUILDER_IP)/altera_avalon_lan91c111/HAL/inc \
		$(SOPC_BUILDER_IP)/altera_avalon_lan91c111/inc \
		$(SOPC_BUILDER_IP)/altera_avalon_lan91c111/UCOSII/inc \
		$(SOPC_BUILDER_IP)/altera_avalon_dma/HAL/inc \
		$(SOPC_BUILDER_IP)/altera_avalon_dma/inc \
		$(SOPC_BUILDER_IP)/altera_avalon_jtag_uart/HAL/inc \
		$(SOPC_BUILDER_IP)/altera_avalon_jtag_uart/inc \
		$(SOPC_BUILDER_IP)/altera_avalon_jtag_uart/LWHAL/inc \
		$(SOPC_BUILDER_IP)/altera_avalon_uart/HAL/inc \
		$(SOPC_BUILDER_IP)/altera_avalon_uart/inc \
		$(SOPC_BUILDER_IP)/altera_avalon_uart/LWHAL/inc \
		$(SOPC_BUILDER_IP)/altera_avalon_sysid_qsys/HAL/inc \
		$(SOPC_BUILDER_IP)/altera_avalon_sysid_qsys/inc \
		$(SOPC_BUILDER_IP)/altera_avalon_performance_counter/HAL/inc \
		$(SOPC_BUILDER_IP)/altera_avalon_sgdma/HAL/inc \
		$(SOPC_BUILDER_IP)/altera_avalon_sgdma/inc \
		$(SOPC_BUILDER_IP)/altera_avalon_lcd_16207/HAL/inc \
		$(SOPC_BUILDER_IP)/altera_avalon_lcd_16207/inc \
		$(ALTERA_IP)/altera_remote_update/HAL/inc \
		$(ALTERA_IP)/altera_remote_update/inc \
		$(ALTERA_IP)/nios2_ip/altera_nios2_gen2/HAL/inc \
		$(ALTERA_IP)/nios2_ip/altera_nios2_gen2/UCOSIII/inc \
		$(ALTERA_IP)/nios2_ip/altera_nios2_gen2/UCOSII/inc \
		$(ALTERA_IP)/nios2_ip/altera_nios2/HAL/inc \
		$(ALTERA_IP)/nios2_ip/altera_nios2/UCOSII/inc \
		$(ALTERA_IP)/altera_onchip_flash/altera_onchip_flash/HAL/inc \
		$(ALTERA_IP)/altera_onchip_flash/altera_onchip_flash/inc \
		$(ALTERA_IP)/altera_vectored_interrupt_controller/top/HAL/inc \
		$(ALTERA_IP)/altera_vectored_interrupt_controller/top/inc \
		$(ALTERA_IP)/vip/ip_library/drivers/vip/inc \
		$(ALTERA_IP)/ethernet/altera_eth_tse/src/software/lib/HAL/inc \
		$(ALTERA_IP)/ethernet/altera_eth_tse/src/software/lib/inc \
		$(ALTERA_IP)/ethernet/altera_eth_tse/src/software/lib/UCOSII/inc \
		$(ALTERA_IP)/altera_avalon_i2c/HAL/inc \
		$(ALTERA_IP)/altera_avalon_i2c/inc \
		$(UNI_PROG_IP)/memory/altera_up_sd_card_avalon_interface/HAL/inc \
		$(UNI_PROG_IP)/communication/altera_up_avalon_rs232/HAL/inc \
		$(UNI_PROG_IP)/communication/altera_up_avalon_irda/HAL/inc \
		$(UNI_PROG_IP_IO)/altera_up_avalon_accelerometer_spi/HAL/inc \
		$(UNI_PROG_IP_IO)/altera_up_avalon_parallel_port/HAL/inc \
		$(UNI_PROG_IP_IO)/altera_up_avalon_usb/HAL/inc \
		$(UNI_PROG_IP_IO)/altera_up_avalon_adc/HAL/inc \
		$(UNI_PROG_IP_IO)/altera_up_avalon_ps2/HAL/inc \
		$(UNI_PROG_IP_IO)/altera_up_avalon_de1_soc_adc/HAL/inc \
		$(UNI_PROG_IP_IO)/altera_up_avalon_de0_nano_adc/HAL/inc \
		$(UNI_PROG_IP_AV)/altera_up_avalon_audio/HAL/inc \
		$(UNI_PROG_IP_AV)/video/altera_up_avalon_video_dma_controller/HAL/inc \
		$(UNI_PROG_IP_AV)/video/altera_up_avalon_video_character_buffer_with_dma/HAL/inc \
		$(UNI_PROG_IP_AV)/video/altera_up_avalon_video_rgb_resampler/HAL/inc \
		$(UNI_PROG_IP_AV)/video/altera_up_avalon_video_pixel_buffer_dma/HAL/inc \
		$(UNI_PROG_IP_AV)/altera_up_avalon_character_lcd/HAL/inc \
		$(UNI_PROG_IP_AV)/altera_up_avalon_audio_and_video_config/HAL/inc \
		$(PGM_IP)/generic_qspi_controller2/HAL/inc \
		$(PGM_IP)/generic_qspi_controller2/inc \
		$(PGM_IP)/altera_epcq_controller2/HAL/inc \
		$(PGM_IP)/altera_epcq_controller2/inc \
		$(ALTERA_IP)/altera_epcq_controller/HAL/inc \
		$(ALTERA_IP)/altera_epcq_controller/inc \
		$(ALTERA_IP)/hps/altera_hps/hwlib/include \
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
	$(CXX) $(CXX_FLAGS) -c -o $@ $<

# Rule to build object files from tests (CTRL_DIR)
$(CTRL_OBJ_DIR)/%.o: $(CTRL_DIR)/%.cpp $(OBJ_FILES)
	$(CXX) $(CXX_FLAGS) -c -o $@ $<

# Rule to link test executables, linking with all object files from src
$(CTRL_EXEC)/%: $(CTRL_OBJ_DIR)/%.o $(OBJ_FILES)
	$(CXX) $(LD_FLAGS) $^ -o $@

.PHONY: clean
clean:
	rm -f $(OBJ_DIR)/*.o $(CTRL_OBJ_DIR)/*.o $(CTRL_OBJ_DIR)/* $(CTRL_EXEC)/*