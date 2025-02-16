#include "main.h"

lfsr_controller::lfsr_controller(std::shared_ptr<memory_manager> memory_manager_instance,
                                 MEM_REGIONS peripheral_memory_region)
    : memory_manager_instance(memory_manager_instance), peripheral_memory_region(peripheral_memory_region)
{
    // Reset the LFSR
    this->memory_manager_instance->write_to_register(FPGA_SLAVES_MEM_REGION, CTRL_REGISTER_BASE, 0x2);
    this->memory_manager_instance->write_to_register(FPGA_SLAVES_MEM_REGION, CTRL_REGISTER_BASE, 0x0);
    this->memory_manager_instance->write_to_register(FPGA_SLAVES_MEM_REGION, CTRL_REGISTER_BASE, 0x2);

    printf("LFSR Controller Initialized\n");
    printf("LSFR Initial Value: 0x%8llx :: %llu\n",
           this->memory_manager_instance->read_from_register(FPGA_SLAVES_MEM_REGION, RANDOM_BASE).value(),
           this->memory_manager_instance->read_from_register(FPGA_SLAVES_MEM_REGION, RANDOM_BASE).value());
}

lfsr_controller::~lfsr_controller()
{
	printf("LFSR Controller Destroyed\n");
}

uint32_t lfsr_controller::get_random_number()
{
    this->memory_manager_instance->write_to_register(this->peripheral_memory_region, CTRL_REGISTER_BASE, 0x3);
    this->memory_manager_instance->write_to_register(this->peripheral_memory_region, CTRL_REGISTER_BASE, 0x2);
    return this->memory_manager_instance->read_from_register(this->peripheral_memory_region, RANDOM_BASE).value();
}

void lfsr_controller::reset()
{
    this->memory_manager_instance->write_to_register(this->peripheral_memory_region, CTRL_REGISTER_BASE, 0x2);
    this->memory_manager_instance->write_to_register(this->peripheral_memory_region, CTRL_REGISTER_BASE, 0x0);
    this->memory_manager_instance->write_to_register(this->peripheral_memory_region, CTRL_REGISTER_BASE, 0x2);
}