#include "main.h"

union reint {
    uint64_t number;
    uint8_t num_arr[8];
};

/*
-set-seed       0x54397546
                3185463565

-seed-type      Base 16
                Base 10

-gen-rand       <amount of rand num>

-rand-out-type  Base 16
                Base 10
*/

void print_help_menu()
{
    printf("Cyclone V LFSR PIO Standalone Controller v0.1 (arm-none-linux-gnueabihf)\n");
    printf("Usage: lfsr_ctrl options\n");
    printf("\t-set-seed <seed>\tSeed is a 32 bit value that can be passed as a base 16, base 10 or base 2 number\n");
    printf("\t\t\t\tNote: Cannot be used with -gen-rand\n");
    printf("\t-seed-type <base>\tBase of the seed, can be 16, 10, or 2\n");

    printf("\t-gen-rand <n>\t\tGenerate a 32bit random number n amount of times\n");
    printf("\t\t\t\tNote: Cannot be used with -set-seed\n");
    printf("\t-rand-out-type <base>\tBase of the random number, can be 16, 10, or 2\n");

    printf("\t-help\t\t\tPrints this menu\n");
    printf("Copyright (C) 2025 by Joshua Estes\n");
}

int main(int argc, char **argv)
{
    if (argc == 1)
    {
        print_help_menu();
        exit(0);
    }

    bool seed_passed = false;
    bool seed_base_passed = false;
    bool gen_rand_passed = false;
    bool rand_type_passed = false;
    bool auto_det_base = false;

    char *seed_str;
    char *seed_base;
    char *amount_of_rand_num;
    char *rand_num_base;

    for (int i = 0; i < argc; i++)
    {
        if (strcmp(argv[i], "-help") == 0)
        {
            print_help_menu();
            exit(0);
        }
        if (strcmp(argv[i], "-set-seed") == 0)
        {
            seed_str = argv[i + 1];
            seed_passed = true;
        }
        if (strcmp(argv[i], "-seed-type") == 0)
        {
            seed_base = argv[i + 1];
            seed_base_passed = true;
        }

        if (strcmp(argv[i], "-gen-rand") == 0)
        {
            amount_of_rand_num = argv[i + 1];
            gen_rand_passed = true;
        }
        if (strcmp(argv[i], "-rand-out-type") == 0)
        {
            rand_num_base = argv[i + 1];
            rand_type_passed = true;
        }
    }

    if (!(seed_passed && seed_base_passed) && !(gen_rand_passed && rand_type_passed))
    {
        printf("Automatically determining base...\n");
        auto_det_base = true;
    }

    std::shared_ptr<memory_manager> memory_manager_instance = std::make_shared<memory_manager>();
    lfsr_controller lfsr_controller(memory_manager_instance, FPGA_SLAVES_MEM_REGION);

    if (seed_passed)
    {
        uint32_t seed;
        if (auto_det_base)
            seed = std::stoi(seed_str);
        else
        {
            int base = std::stoi(seed_base, nullptr, 10);
            seed = std::stoi(seed_str, nullptr, base);
        }

        lfsr_controller.set_seed(seed);

        exit(0);
    }

    if (gen_rand_passed)
    {
        uint32_t amnt_of_rand_num = std::stoi(amount_of_rand_num);

        int base = 10;
        if (rand_type_passed)
            base = std::stoi(rand_num_base, nullptr, 10);

        for (uint32_t i = 0; i < amnt_of_rand_num; i++)
        {
            uint32_t rand_num = lfsr_controller.get_random_number();

            if (auto_det_base)
                printf("%d: 0x%08x :: %u\n", i, rand_num, rand_num);
            else if (base == 10)
                printf("%d: %u\n", i, rand_num);
            else if (base == 16)
                printf("%d: 0x%08x\n", i, rand_num);
            else
            {
                printf("Unrecognized base\n");
                exit(0);
            }
        }

        exit(0);
    }

    exit(0);
}