#include "main.h"

led_control::led_control(std::shared_ptr<memory_manager> memory_manager_instance)
{
	this->memory_manager_instance = memory_manager_instance;
}

led_control::~led_control()
{
}

void led_control::clear_led_bits()
{
	this->memory_manager_instance->write_to_register(FPGA_SLAVES_MEM_REGION, LED_PIO_BASE, 0);
}

void led_control::set_led_bits(uint8_t mask)
{
    this->memory_manager_instance->write_to_register(FPGA_SLAVES_MEM_REGION, LED_PIO_BASE, mask);
}