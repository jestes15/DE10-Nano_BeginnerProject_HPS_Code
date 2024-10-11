#ifndef F3D76B28_62F0_421B_95AA_C26A50499045
#define F3D76B28_62F0_421B_95AA_C26A50499045

// C++ Header Files
#include <cinttypes>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>

// C Header File
#include <error.h>

// Linux Header Files
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>

// HPS-FPGA Specific Header Files
#include "hps_0.h"

#include "io_addr_macros.h"
#include "io_rw_macros.h"

// Common Address Space Regions
#define FPGASLAVES 0xC0000000
#define PERIPH 0xFC000000
#define LWFPGASLAVES 0xFF200000

#define HPS_TO_FPGA_HW_BASE 0xC0000000
#define HPS_TO_FPGA_HW_SPAN 0x00100017

#define HPS_TO_FPGA_HW_ADDER_BASE 0xC0000000 + 0x00100000
#define HPS_TO_FPGA_HW_ADDER_SPAN 0x17

#endif /* F3D76B28_62F0_421B_95AA_C26A50499045 */
