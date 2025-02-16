#include "main.h"

led_control::led_control(std::shared_ptr<memory_manager> memory_manager_instance, MEM_REGIONS peripheral_memory_region)
    : memory_manager_instance(memory_manager_instance), peripheral_memory_region(peripheral_memory_region)
{
	printf("LED Controller initialized\n");
}

led_control::~led_control()
{
	printf("LED Controller Destroyed\n");
}

void led_control::clear_led_bits()
{
    this->memory_manager_instance->write_to_register(this->peripheral_memory_region, LED_PIO_BASE, 0);
}

void led_control::set_led_bits(uint8_t mask)
{
    this->memory_manager_instance->write_to_register(this->peripheral_memory_region, LED_PIO_BASE, mask);
}