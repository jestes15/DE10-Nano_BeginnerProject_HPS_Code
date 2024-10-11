#ifndef E10A7468_4384_4E81_A188_CFCD054C63A7
#define E10A7468_4384_4E81_A188_CFCD054C63A7

#include <cinttypes>

#define IORD_8DIRECT(base, offset) *((volatile uint8_t *)((base) + (offset)))
#define IORD_16DIRECT(base, offset) *((volatile uint16_t *)((base) + (offset)))
#define IORD_32DIRECT(base, offset) *((volatile uint32_t *)((base) + (offset)))
#define IORD_64DIRECT(base, offset) *((volatile uint64_t *)((base) + (offset)))

#define IOWR_8DIRECT(base, offset, value) *((volatile uint8_t *)((base) + (offset))) = (value)
#define IOWR_16DIRECT(base, offset, value) *((volatile uint16_t *)((base) + (offset))) = (value)
#define IOWR_32DIRECT(base, offset, value) *((volatile uint32_t *)((base) + (offset))) = (value)
#define IOWR_64DIRECT(base, offset, value) *((volatile uint64_t *)((base) + (offset))) = (value)

#endif /* E10A7468_4384_4E81_A188_CFCD054C63A7 */
