#include "main.h"

union reint {
    uint64_t number;
    uint8_t num_arr[8];
};

int main(int argc, char **argv)
{
    std::shared_ptr<memory_manager> memory_manager_instance = std::make_shared<memory_manager>();
    lfsr_controller lfsr_controller(memory_manager_instance, FPGA_SLAVES_MEM_REGION, 0x12345678);

    for (int i = 0; i < 32; i++)
    {
        auto temp = lfsr_controller.get_random_number();
        printf("Random Number: 0x%08x :: %u\n", temp, temp);
    }
}