#ifndef F3D76B28_62F0_421B_95AA_C26A50499045
#define F3D76B28_62F0_421B_95AA_C26A50499045

// spdlog Header Files
#include "spdlog/spdlog.h"

// C++ Header Files
#include <cinttypes>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <exception>
#include <optional>

// C Header File
#include <error.h>

// Linux Header Files
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>

// HPS-FPGA Specific Header Files
#include <hwlib.h>
#include <socal/alt_gpio.h>
#include <socal/hps.h>
#include <socal/socal.h>

#include "hps_0.h"
#include "soc_system.h"

// Macro Header Files
#include "io_addr_macros.h"
#include "io_rw_macros.h"

// Enumerations for Memory Regions
enum MEM_REGIONS
{
    FPGA_SLAVES_MEM_REGION,
    PERIPH_MEM_REGION,
    LW_FPGA_SLAVES_MEM_REGION
};

// Enumerations for memory_manager errors
enum MEMORY_MANAGER_ERRORS
{
    MEM_REGION_NOT_VALID
};

// Common Address Space Regions
#define FPGASLAVES 0xC0000000
#define PERIPH 0xFC000000
#define LWFPGASLAVES 0xFF200000

// Common Address Space Spans
#define FPGASLAVES_SPAN 0x3C000000
#define PERIPH_SPAN 0x04000000
#define LWFPGASLAVES_SPAN 0x00200000

class memory_manager
{
  private:
    std::shared_ptr<uint8_t> fpga_slaves_base;
    std::shared_ptr<uint8_t> periph_base;
    std::shared_ptr<uint8_t> lw_fpga_slaves_base;
    int file_descriptor;

  public:
    memory_manager();
    ~memory_manager();

	std::optional<uint8_t> or_register(MEM_REGIONS memory_region, uint64_t offset, uint64_t value);
	std::optional<uint8_t> and_register(MEM_REGIONS memory_region, uint64_t offset, uint64_t value);
	std::optional<uint8_t> xor_register(MEM_REGIONS memory_region, uint64_t offset, uint64_t value);
	std::optional<uint8_t> not_register(MEM_REGIONS memory_region, uint64_t offset);
	
    std::optional<uint8_t> write_to_register(MEM_REGIONS memory_region, uint64_t offset, uint64_t value);
    std::optional<uint64_t> read_from_register(MEM_REGIONS memory_region, uint64_t offset);
    std::optional<uint8_t> clear_register(MEM_REGIONS memory_region, uint64_t offset);
};

class led_control
{
  private:
    std::shared_ptr<memory_manager> memory_manager_instance;

  public:
    led_control(std::shared_ptr<memory_manager> memory_manager_instance);
    ~led_control();

    void clear_led_bits();
    void set_led_bits(uint8_t mask);
};

class lfsr_controller
{
  private:
    std::shared_ptr<memory_manager> memory_manager_instance;
	uint64_t lsfr_control_register;

  public:
    lfsr_controller(std::shared_ptr<memory_manager> memory_manager_instance);
    ~lfsr_controller();

    uint32_t get_random_number();
	void reset();
};

#endif /* F3D76B28_62F0_421B_95AA_C26A50499045 */
