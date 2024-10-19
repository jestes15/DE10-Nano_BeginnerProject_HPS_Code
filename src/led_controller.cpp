#include "main.h"

led_control::led_control()
{
    file_descriptor = open("/dev/mem", O_RDWR | O_SYNC);

    if (file_descriptor < 0)
    {
        printf("Could not open /dev/mem: open returned %d", file_descriptor);
        // throw std::runtime_error("Could not open /dev/mem");

        exit(1);
    }

    fpga_slaves_base = (uint8_t *)mmap(NULL, 0x0050, PROT_READ | PROT_WRITE, MAP_SHARED, file_descriptor, 0xC0000000);
    if (fpga_slaves_base == MAP_FAILED)
    {
        printf("Could not map bridge: mmap returned %p", fpga_slaves_base);
        close(file_descriptor);
        throw std::runtime_error("Could not map bridge");
    }

    led_register = fpga_slaves_base + 0x00000020;
}

led_control::~led_control()
{
    int temp = munmap(fpga_slaves_base, 0x0050);
    if (temp < 0)
        printf("Could not unmap bridge: munmap returned %d", temp);

    close(file_descriptor);
}

void led_control::clear_led_bits()
{
    *((volatile uint8_t *)(led_register)) = 0;
}

void led_control::set_led_bits(uint8_t mask)
{
    *((volatile uint8_t *)(led_register)) = mask;
}