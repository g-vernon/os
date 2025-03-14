#include <stdint.h>

typedef struct {
	uint16_t limit; /* Least 16 bits of 20-bit limit */
	uint16_t base_low;
	uint8_t base_middle;
	uint8_t access;
	uint8_t flags; /* Bits 7-4 flags, bits 3-0 greatest 4 bits of 20-bit limit*/
	uint8_t base_high;
} __attribute__((packed)) GdtEntry;

typedef struct {
	uint16_t limit;
	uint32_t base;
} __attribute__((packed)) GdtPtr;

void init_gdt();
