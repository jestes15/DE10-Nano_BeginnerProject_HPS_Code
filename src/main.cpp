#include "main.h"

union reint {
    uint64_t number;
    uint8_t num_arr[8];
};

#define HPS_TO_FPGA_HW_ADDER_SPAN 0x18
#define HPS_TO_FPGA_HW_ADDER_BASE 0xC0000000

int main(int argc, char **argv)
{
    led_control led_controller;

    led_controller.clear_led_bits();
    usleep(1000 * 500);

    printf("Hello World\n");

    for (int i = 0; i < 8; i++)
    {
        led_controller.set_led_bits(1 << i);
        usleep(1000 * 500);
    }
    // Variables
    // reint reg_a;
    // reint reg_b;
    // uint64_t sum = 0;

    // int fd = 0;
    // int result = 0;
    // uint8_t *FPGA_Slaves_Base = NULL;
    // uint8_t *operand_a_map = NULL;
    // uint8_t *operand_b_map = NULL;
    // uint8_t *sum_map = NULL;

    // // Argument checks
    // if (argc != 3)
    // {
    //     printf("More/less arguments than expected. (Max 2 arguments)\n");
    //     return -1;
    // }

    // // Argument preperation
    // reg_a.number = strtoll(argv[1], NULL, 10);
    // reg_b.number = strtoll(argv[2], NULL, 10);

    // fd = open("/dev/mem", O_RDWR | O_SYNC);
    // if (fd < 0)
    // {
    //     printf("Couldn't open /dev/mem\n");
    //     return -2;
    // }

    // FPGA_Slaves_Base = (uint8_t *)mmap(NULL, HPS_TO_FPGA_HW_ADDER_SPAN, PROT_READ | PROT_WRITE, MAP_SHARED, fd,
    //                                    HPS_TO_FPGA_HW_ADDER_BASE);
    // if (FPGA_Slaves_Base == MAP_FAILED)
    // {
    //     printf("Couldn't map bridge\n");
    //     close(fd);
    //     return -3;
    // }

    // operand_a_map = FPGA_Slaves_Base;
    // operand_b_map = FPGA_Slaves_Base + 0x08;
    // sum_map = FPGA_Slaves_Base + 0x10;

    // printf("A_Base: %x\n", HPS_TO_FPGA_HW_ADDER_BASE);
    // printf("A: %p, B: %p, Sum: %p\n", operand_a_map, operand_b_map, sum_map);

    // *((uint64_t *)operand_a_map) = reg_a.number;
    // *((uint64_t *)operand_b_map) = reg_b.number;

    // sum = *((uint64_t *)sum_map);

    // printf("%" PRIu64 "\n", sum);

    // result = munmap(FPGA_Slaves_Base, HPS_TO_FPGA_HW_ADDER_SPAN);

    // if (result < 0)
    // {
    //     printf("Couldn't unmap bridge\n");
    //     close(fd);
    //     return -4;
    // }

    // close(fd);
    // return 0;
}