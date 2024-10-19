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

// C Header File
#include <error.h>

// Linux Header Files
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>

// HPS-FPGA Specific Header Files
#include <hwlib.h>
#include <socal/socal.h>
#include <socal/hps.h>
#include <socal/alt_gpio.h>

#include "hps_0.h"
#include "soc_system.h"

// Macro Header Files
#include "io_addr_macros.h"
#include "io_rw_macros.h"

// Common Address Space Regions
#define FPGASLAVES 0xC0000000
#define PERIPH 0xFC000000
#define LWFPGASLAVES 0xFF200000

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

    uint8_t *get_fpga_slaves_base();
    uint8_t *get_periph_base();
    uint8_t *get_lw_fpga_slaves_base();
};

class led_control
{
  private:
    std::shared_ptr<memory_manager> memory_manager_instance;

  public:
    led_control();
    ~led_control();

    void clear_led_bits();
    void set_led_bits(uint8_t mask);
};

#endif /* F3D76B28_62F0_421B_95AA_C26A50499045 */
