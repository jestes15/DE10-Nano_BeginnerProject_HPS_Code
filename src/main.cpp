#include "main.h"

union reint {
    uint64_t number;
    uint8_t num_arr[8];
};

#define HPS_TO_FPGA_HW_ADDER_SPAN 0x18
#define HPS_TO_FPGA_HW_ADDER_BASE 0xC0000000

int main(int argc, char **argv)
{
    std::shared_ptr<memory_manager> memory_manager_instance = std::make_shared<memory_manager>();
    led_control led_controller(memory_manager_instance);
    lfsr_controller lfsr_controller(memory_manager_instance);

    led_controller.clear_led_bits();
    usleep(1000 * 500);

    for (int i = 0; i < 8; i++)
    {
        led_controller.set_led_bits(1 << i);
        printf("Random Number: 0x%8x\n", lfsr_controller.get_random_number());
        usleep(1000 * 500);
    }
}