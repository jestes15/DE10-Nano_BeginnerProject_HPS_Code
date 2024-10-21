#include "main.h"

memory_manager::memory_manager()
{
    file_descriptor = open("/dev/mem", O_RDWR | O_SYNC);
    if (file_descriptor == -1)
        throw std::runtime_error("Failed to open /dev/mem");

    fpga_slaves_base =
        std::shared_ptr<uint8_t>(reinterpret_cast<uint8_t *>(mmap(nullptr, FPGASLAVES_SPAN, PROT_READ | PROT_WRITE,
                                                                  MAP_SHARED, file_descriptor, FPGASLAVES)),
                                 [this](uint8_t *p) { munmap(p, FPGASLAVES_SPAN); });

    if (fpga_slaves_base.get() == MAP_FAILED)
        throw std::runtime_error("Failed to map FPGA slaves base address");

    periph_base =
        std::shared_ptr<uint8_t>(reinterpret_cast<uint8_t *>(mmap(nullptr, PERIPH_SPAN, PROT_READ | PROT_WRITE,
                                                                  MAP_SHARED, file_descriptor, PERIPH)),
                                 [this](uint8_t *p) { munmap(p, PERIPH_SPAN); });

    if (periph_base.get() == MAP_FAILED)
        throw std::runtime_error("Failed to map peripheral base address");

    lw_fpga_slaves_base =
        std::shared_ptr<uint8_t>(reinterpret_cast<uint8_t *>(mmap(nullptr, LWFPGASLAVES_SPAN, PROT_READ | PROT_WRITE,
                                                                  MAP_SHARED, file_descriptor, LWFPGASLAVES)),
                                 [this](uint8_t *p) { munmap(p, LWFPGASLAVES_SPAN); });

    if (lw_fpga_slaves_base.get() == MAP_FAILED)
        throw std::runtime_error("Failed to map lightweight FPGA slaves base address");
}

memory_manager::~memory_manager()
{
    close(file_descriptor);
}

std::optional<uint8_t> memory_manager::or_register(MEM_REGIONS memory_region, uint64_t offset, uint64_t value)
{
	switch (memory_region)
	{
	case FPGA_SLAVES_MEM_REGION:
		IOWR_64DIRECT(this->fpga_slaves_base.get(), offset, IORD_64DIRECT(this->fpga_slaves_base.get(), offset) | value);
		break;
	case PERIPH_MEM_REGION:
		IOWR_64DIRECT(this->periph_base.get(), offset, IORD_64DIRECT(this->periph_base.get(), offset) | value);
		break;
	case LW_FPGA_SLAVES_MEM_REGION:
		IOWR_64DIRECT(this->lw_fpga_slaves_base.get(), offset, IORD_64DIRECT(this->lw_fpga_slaves_base.get(), offset) | value);
		break;
	default:
		return MEM_REGION_NOT_VALID;
	}

	return {};
}

std::optional<uint8_t> memory_manager::and_register(MEM_REGIONS memory_region, uint64_t offset, uint64_t value)
{
	switch (memory_region)
	{
	case FPGA_SLAVES_MEM_REGION:
		IOWR_64DIRECT(this->fpga_slaves_base.get(), offset, IORD_64DIRECT(this->fpga_slaves_base.get(), offset) & value);
		break;
	case PERIPH_MEM_REGION:
		IOWR_64DIRECT(this->periph_base.get(), offset, IORD_64DIRECT(this->periph_base.get(), offset) & value);
		break;
	case LW_FPGA_SLAVES_MEM_REGION:
		IOWR_64DIRECT(this->lw_fpga_slaves_base.get(), offset, IORD_64DIRECT(this->lw_fpga_slaves_base.get(), offset) & value);
		break;
	default:
		return MEM_REGION_NOT_VALID;
	}

	return {};
}

std::optional<uint8_t> memory_manager::xor_register(MEM_REGIONS memory_region, uint64_t offset, uint64_t value)
{
	switch (memory_region)
	{
	case FPGA_SLAVES_MEM_REGION:
		IOWR_64DIRECT(this->fpga_slaves_base.get(), offset, IORD_64DIRECT(this->fpga_slaves_base.get(), offset) ^ value);
		break;
	case PERIPH_MEM_REGION:
		IOWR_64DIRECT(this->periph_base.get(), offset, IORD_64DIRECT(this->periph_base.get(), offset) ^ value);
		break;
	case LW_FPGA_SLAVES_MEM_REGION:
		IOWR_64DIRECT(this->lw_fpga_slaves_base.get(), offset, IORD_64DIRECT(this->lw_fpga_slaves_base.get(), offset) ^ value);
		break;
	default:
		return MEM_REGION_NOT_VALID;
	}

	return {};
}

std::optional<uint8_t> memory_manager::not_register(MEM_REGIONS memory_region, uint64_t offset)
{
	switch (memory_region)
	{
	case FPGA_SLAVES_MEM_REGION:
		IOWR_64DIRECT(this->fpga_slaves_base.get(), offset, ~IORD_64DIRECT(this->fpga_slaves_base.get(), offset));
		break;
	case PERIPH_MEM_REGION:
		IOWR_64DIRECT(this->periph_base.get(), offset, ~IORD_64DIRECT(this->periph_base.get(), offset));
		break;
	case LW_FPGA_SLAVES_MEM_REGION:
		IOWR_64DIRECT(this->lw_fpga_slaves_base.get(), offset, ~IORD_64DIRECT(this->lw_fpga_slaves_base.get(), offset));
		break;
	default:
		return MEM_REGION_NOT_VALID;
	}

	return {};
}

std::optional<uint8_t> memory_manager::bic_register(MEM_REGIONS memory_region, uint64_t offset, uint64_t value)
{
	switch (memory_region)
	{
	case FPGA_SLAVES_MEM_REGION:
		IOWR_64DIRECT(this->fpga_slaves_base.get(), offset, IORD_64DIRECT(this->fpga_slaves_base.get(), offset) & ~value);
		break;
	case PERIPH_MEM_REGION:
		IOWR_64DIRECT(this->periph_base.get(), offset, IORD_64DIRECT(this->periph_base.get(), offset) & ~value);
		break;
	case LW_FPGA_SLAVES_MEM_REGION:
		IOWR_64DIRECT(this->lw_fpga_slaves_base.get(), offset, IORD_64DIRECT(this->lw_fpga_slaves_base.get(), offset) & ~value);
		break;
	default:
		return MEM_REGION_NOT_VALID;
	}

	return {};
}

std::optional<uint8_t> memory_manager::bis_register(MEM_REGIONS memory_region, uint64_t offset, uint64_t value)
{
	switch (memory_region)
	{
	case FPGA_SLAVES_MEM_REGION:
		IOWR_64DIRECT(this->fpga_slaves_base.get(), offset, IORD_64DIRECT(this->fpga_slaves_base.get(), offset) | value);
		break;
	case PERIPH_MEM_REGION:
		IOWR_64DIRECT(this->periph_base.get(), offset, IORD_64DIRECT(this->periph_base.get(), offset) | value);
		break;
	case LW_FPGA_SLAVES_MEM_REGION:
		IOWR_64DIRECT(this->lw_fpga_slaves_base.get(), offset, IORD_64DIRECT(this->lw_fpga_slaves_base.get(), offset) | value);
		break;
	default:
		return MEM_REGION_NOT_VALID;
	}

	return {};
}

std::optional<uint8_t> memory_manager::write_to_register(MEM_REGIONS memory_region, uint64_t offset, uint64_t value)
{
    switch (memory_region)
    {
    case FPGA_SLAVES_MEM_REGION:
        IOWR_64DIRECT(this->fpga_slaves_base.get(), offset, value);
        break;
    case PERIPH_MEM_REGION:
        IOWR_64DIRECT(this->periph_base.get(), offset, value);
        break;
    case LW_FPGA_SLAVES_MEM_REGION:
        IOWR_64DIRECT(this->lw_fpga_slaves_base.get(), offset, value);
        break;
    default:
        return MEM_REGION_NOT_VALID;
    }

    return {};
}

std::optional<uint64_t> memory_manager::read_from_register(MEM_REGIONS memory_region, uint64_t offset)
{
    switch (memory_region)
    {
    case FPGA_SLAVES_MEM_REGION:
        return IORD_64DIRECT(this->fpga_slaves_base.get(), offset);
    case PERIPH_MEM_REGION:
        return IORD_64DIRECT(this->periph_base.get(), offset);
    case LW_FPGA_SLAVES_MEM_REGION:
        return IORD_64DIRECT(this->lw_fpga_slaves_base.get(), offset);
    default:
        return {};
    }
}

std::optional<uint8_t> memory_manager::clear_register(MEM_REGIONS memory_region, uint64_t offset)
{
    switch (memory_region)
    {
    case FPGA_SLAVES_MEM_REGION:
        IOWR_64DIRECT(this->fpga_slaves_base.get(), offset, 0);
        break;
    case PERIPH_MEM_REGION:
        IOWR_64DIRECT(this->periph_base.get(), offset, 0);
        break;
    case LW_FPGA_SLAVES_MEM_REGION:
        IOWR_64DIRECT(this->lw_fpga_slaves_base.get(), offset, 0);
        break;
    default:
        return MEM_REGION_NOT_VALID;
    }

    return {};
}