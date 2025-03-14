#include "gdt.h"

/* Access byte masks */
#define PRESENT(x) ((x) << 7)
#define DPL(x) (((x) & 0x03) << 5) /* Privilege level */
#define DESC_TYPE(x) ((x) << 4) /* 0 = system segment, 1 = code or data */
#define EXECUTABLE(x) ((x) << 3)
#define DIRECTION(x) ((x) << 2)
#define RW(x) ((x) << 1)
#define ACCESSED(x) (x)

/* Flag nibble masks */
#define GRANULARITY(x) ((x) << 3)
#define SIZE(x) ((x) << 2) /* 0 = 16-bit, 1 = 32-bit */
#define LONGMODE(x) ((x) << 1)
#define RESERVED 0x1

/* Access bytes */
#define KCODE_ACCESS PRESENT(1) | DESC_TYPE(1) | EXECUTABLE(1) | RW(1)
#define KDATA_ACCESS PRESENT(1) | DESC_TYPE(1) | RW(1)

#define UCODE_ACCESS PRESENT(1) | DPL(3) | DESC_TYPE(1) | EXECUTABLE(1) | RW(1)
#define UDATA_ACCESS PRESENT(1) | DPL(3) | DESC_TYPE(1) | RW(1)

/* Flags */
#define FLAGS GRANULARITY(1) | SIZE(1)

extern void load_seg_registers(uint32_t addr);

void set_gdt_entry(uint32_t entry, uint32_t base, uint32_t limit,
		   uint8_t access, uint8_t flags);

GdtEntry gdt[5];
GdtPtr gdt_ptr;

void init_gdt()
{
	gdt_ptr.limit = sizeof(gdt) - 1;
	gdt_ptr.base = (uint32_t)&gdt;

	set_gdt_entry(0, 0, 0, 0, 0); /* Null descriptor */
	set_gdt_entry(1, 0, 0xFFFFFFFF, KCODE_ACCESS,
		      FLAGS); /* Kernel code segment */
	set_gdt_entry(2, 0, 0xFFFFFFFF, KDATA_ACCESS,
		      FLAGS); /* Kernel data segment */
	set_gdt_entry(3, 0, 0xFFFFFFFF, UCODE_ACCESS,
		      FLAGS); /* User code segment */
	set_gdt_entry(4, 0, 0xFFFFFFFF, UDATA_ACCESS,
		      FLAGS); /* User data segment */

	load_seg_registers((uint32_t)&gdt_ptr);
}

void set_gdt_entry(uint32_t entry, uint32_t base, uint32_t limit,
		   uint8_t access, uint8_t flags)
{
	gdt[entry].base_low = base & 0xFFFF;
	gdt[entry].base_middle = (base >> 16) & 0xFF;
	gdt[entry].base_high = (base >> 24) & 0xFF;
	gdt[entry].limit = limit & 0xFFFF;
	gdt[entry].flags = (limit >> 16) & 0xF;
	gdt[entry].flags |= (flags & 0xF) << 4;
	gdt[entry].access = access;
}
