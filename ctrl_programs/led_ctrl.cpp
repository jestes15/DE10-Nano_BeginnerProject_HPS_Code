#include "main.h"

int main(int argc, char **argv)
{
    if (argc == 1 || argc > 3)
    {
        printf("Cyclone V LED PIO Standalone Controller v0.1 (arm-none-linux-gnueabihf)\n");
        printf("Usage: led_ctrl options [register value]\n");
        printf("\t-turn-off-leds\t\t\t\tTurn off LEDs on the DE10-Nano Dev Board\n");
        printf(
            "\t-set-led-reg <register contents>\tSet the LED PIO register to the value in <register contents>\n\n\n");
        printf("Copyright (C) 2025 by Joshua Estes\n");

        exit(0);
    }

    std::shared_ptr<memory_manager> memory_manager_instance = std::make_shared<memory_manager>();
    led_control led_controller(memory_manager_instance, LW_FPGA_SLAVES_MEM_REGION);

    if (strcmp(argv[1], "-turn-off-leds") == 0)
    {
        led_controller.clear_led_bits();
    }
    else if (strcmp(argv[1], "-set-led-reg") == 0)
    {
        uint8_t reg = static_cast<uint8_t>(std::stoi(argv[2]));
        led_controller.set_led_bits(reg);
    }

    exit(0);
}