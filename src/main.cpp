#include "main.h"

int main(int argc, char **argv)
{
    std::shared_ptr<memory_manager> memory_manager_instance = std::make_shared<memory_manager>();
    led_control led_controller(memory_manager_instance);

    led_controller.clear_led_bits();
    usleep(1000 * 500);
}