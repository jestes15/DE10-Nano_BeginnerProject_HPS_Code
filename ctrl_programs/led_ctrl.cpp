#include "main.h"

int main(int argc, char **argv)
{
    std::shared_ptr<memory_manager> memory_manager_instance = std::make_shared<memory_manager>();
    led_control led_controller(memory_manager_instance, LW_FPGA_SLAVES_MEM_REGION);

    for (int i = 0; i < argc; i++)
    {
        printf("argc[%d): %s\n", i, argv[i]);
    }
}