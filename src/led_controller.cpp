#include "main.h"

led_control::led_control()
{
    file_descriptor = open("/dev/mem", O_RDWR | O_SYNC);
    if (file_descriptor < 0)
    {
        printf("Could not open /dev/mem: open returned %d", file_descriptor);
        throw std::runtime_error("Could not open /dev/mem");
    }

    led_register =
        (uint8_t *)mmap(NULL, LED_PIO_SPAN, PROT_READ | PROT_WRITE, MAP_SHARED, file_descriptor, LED_PIO_BASE);
    if (led_register == MAP_FAILED)
    {
        printf("Could not map bridge: mmap returned %p", led_register);
        close(file_descriptor);
        // throw std::runtime_error("Could not map bridge");
    }
}

led_control::~led_control()
{
    int temp = munmap(led_register, LED_PIO_SPAN);
    if (temp < 0)
        printf("Could not unmap bridge: munmap returned %d", temp);

    close(file_descriptor);
}

void led_control::clear_led_bits()
{
    *((volatile uint64_t *)(led_register)) = 0;
}

void led_control::set_led_bits(uint8_t mask)
{
    *((volatile uint64_t *)(led_register)) = mask;
}