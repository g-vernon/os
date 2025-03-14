#include <stdint.h>

typedef struct {
	uint16_t limit;
	uint16_t base_low;
	uint8_t base_middle;
	uint8_t access;
	uint8_t flags;
	uint8_t base_high;
} __attribute__((packed)) GdtEntry;

typedef struct {
	uint16_t limit;
	uint32_t base;
} __attribute__((packed)) GdtPtr;

void init_gdt();
