#include "main.h"

int main(int argc, char **argv)
{
    // Variables
    uint64_t operand_a = 0;
    uint64_t operand_b = 0;
    uint64_t sum = 0;

    int fd = 0;
    int result = 0;
    uint8_t *bridge_map = NULL;
    uint8_t *operand_a_map = NULL;
    uint8_t *operand_b_map = NULL;
    uint8_t *sum_map = NULL;

    // Argument checks
    if (argc != 3)
    {
        printf("More/less arguments than expected. (Max 2 arguments)");
        return -1;
    }

    // Argument preperation
    operand_a = strtoll(argv[1], NULL, 10);
    operand_b = strtoll(argv[2], NULL, 10);

    fd = open("/dev/mem", O_RDWR | O_SYNC);
    if (fd < 0)
    {
        printf("Couldn't open /dev/mem\n");
        return -2;
    }

    bridge_map = (uint8_t *)mmap(NULL, HPS_TO_FPGA_HW_ADDER_SPAN, PROT_READ | PROT_WRITE, MAP_SHARED, fd,
                                 HPS_TO_FPGA_HW_ADDER_BASE);
    if (bridge_map == MAP_FAILED)
    {
        printf("Couldn't map bridge\n");
        close(fd);
        return -3;
    }

    operand_a_map = bridge_map + PIO_N_OUT_0_BASE;
    operand_b_map = bridge_map + PIO_N_OUT_1_BASE;
    sum_map = bridge_map + PIO_N_IN_0_BASE;

    *((uint64_t *)operand_a_map) = operand_a;
    *((uint64_t *)operand_b_map) = operand_b;
    sum = *((uint64_t *)sum_map);

    printf("%" PRIu64 "\n", sum);

    result = munmap(bridge_map, HPS_TO_FPGA_HW_SPAN);

    if (result < 0)
    {
        printf("Couldn't unmap bridge\n");
        close(fd);
        return -4;
    }

    close(fd);
    return 0;
}