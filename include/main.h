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
#include "hps_0_arm_a9_0.h"
#include "soc_system.h"

// Macro Header Files
#include "io_addr_macros.h"
#include "io_rw_macros.h"

// Common Address Space Regions
#define FPGASLAVES 0xC0000000
#define PERIPH 0xFC000000
#define LWFPGASLAVES 0xFF200000

class led_control
{
  private:
    uint8_t *led_register;
    int file_descriptor;

  public:
    led_control();
    ~led_control();

    void clear_led_bits();
    void set_led_bits(uint8_t mask);
};

#endif /* F3D76B28_62F0_421B_95AA_C26A50499045 */
