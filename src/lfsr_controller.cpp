#include "main.h"

lfsr_controller::lfsr_controller(std::shared_ptr<memory_manager> memory_manager_instance)
{
    this->memory_manager_instance = memory_manager_instance;

    // Reset the LFSR

    this->memory_manager_instance->write_to_register(FPGA_SLAVES_MEM_REGION, CTRL_REGISTER_BASE, 0x2);
    this->memory_manager_instance->write_to_register(FPGA_SLAVES_MEM_REGION, CTRL_REGISTER_BASE, 0x0);
    this->memory_manager_instance->write_to_register(FPGA_SLAVES_MEM_REGION, CTRL_REGISTER_BASE, 0x2);

    printf("LFSR Controller Initialized\n");
    printf("LSFR Initial Value: 0x%8llx\n",
           this->memory_manager_instance->read_from_register(FPGA_SLAVES_MEM_REGION, RANDOM_BASE).value());
}

lfsr_controller::~lfsr_controller()
{
}

uint32_t lfsr_controller::get_random_number()
{
    this->memory_manager_instance->write_to_register(FPGA_SLAVES_MEM_REGION, CTRL_REGISTER_BASE, 0x3);
    this->memory_manager_instance->write_to_register(FPGA_SLAVES_MEM_REGION, CTRL_REGISTER_BASE, 0x2);
    return this->memory_manager_instance->read_from_register(FPGA_SLAVES_MEM_REGION, RANDOM_BASE).value();
}

void lfsr_controller::reset()
{
    this->memory_manager_instance->write_to_register(FPGA_SLAVES_MEM_REGION, CTRL_REGISTER_BASE, 0x2);
    this->memory_manager_instance->write_to_register(FPGA_SLAVES_MEM_REGION, CTRL_REGISTER_BASE, 0x0);
    this->memory_manager_instance->write_to_register(FPGA_SLAVES_MEM_REGION, CTRL_REGISTER_BASE, 0x2);
}