#include "main.h"

memory_manager::memory_manager()
{
    file_descriptor = open("/dev/mem", O_RDWR | O_SYNC);
    if (file_descriptor == -1)
    {
        spdlog::error("Failed to open /dev/mem");
        throw std::exception();
    }

    fpga_slaves_base =
        std::shared_ptr<uint8_t>(reinterpret_cast<uint8_t *>(mmap(nullptr, 0x100000, PROT_READ | PROT_WRITE, MAP_SHARED,
                                                                  file_descriptor, FPGASLAVES)),
                                 [this](uint8_t *p) {
                                     munmap(p, 0x100000);
                                     close(file_descriptor);
                                 });

    if (fpga_slaves_base.get() == MAP_FAILED)
    {
        spdlog::error("Failed to map FPGA slaves base address");
        throw std::exception();
    }

    periph_base = std::shared_ptr<uint8_t>(reinterpret_cast<uint8_t *>(mmap(nullptr, 0x100000, PROT_READ | PROT_WRITE,
                                                                            MAP_SHARED, file_descriptor, PERIPH)),
                                           [this](uint8_t *p) {
                                               munmap(p, 0x100000);
                                               close(file_descriptor);
                                           });

    if (periph_base.get() == MAP_FAILED)
    {
        spdlog::error("Failed to map peripheral base address");
        throw std::exception();
    }

    lw_fpga_slaves_base =
        std::shared_ptr<uint8_t>(reinterpret_cast<uint8_t *>(mmap(nullptr, 0x100000, PROT_READ | PROT_WRITE, MAP_SHARED,
                                                                  file_descriptor, LWFPGASLAVES)),
                                 [this](uint8_t *p) {
                                     munmap(p, 0x100000);
                                     close(file_descriptor);
                                 });

    if (lw_fpga_slaves_base.get() == MAP_FAILED)
    {
        spdlog::error("Failed to map lightweight FPGA slaves base address");
        throw std::exception();
    }
}