#include "gdt.h"

#include <string.h>

/* File config */
#define GDT_SIZE 6

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

#define TSS_ACCESS \
	PRESENT(1) | DPL(3) | DESC_TYPE(0) | EXECUTABLE(1) | ACCESSED(1)

/* Flags */
#define FLAGS GRANULARITY(1) | SIZE(1)
#define TSS_FLAGS SIZE(1)

extern void load_seg_registers(uint32_t addr);
extern void load_tss(void);

void set_gdt_entry(uint32_t entry, uint32_t base, uint32_t limit,
		   uint8_t access, uint8_t flags);

GdtEntry gdt[GDT_SIZE];
GdtPtr gdt_ptr;
TssEntry tss;

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

	write_tss(5, 0x10, 0x0);
	load_seg_registers((uint32_t)&gdt_ptr);
	load_tss();
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

void write_tss(uint32_t num, uint16_t ss0, uint32_t esp0)
{
	const uint32_t base = (uint32_t)&tss;
	const uint32_t limit = sizeof(tss) - 1;

	set_gdt_entry(num, base, limit, TSS_ACCESS, TSS_FLAGS);
	memset(&tss, 0, sizeof(tss));
	tss.ss0 = ss0;
	tss.esp0 = esp0;
	tss.cs = 0x08 | 0x3; /* Setting privilege level to ring 3 */
	tss.ss = tss.ds = tss.es = tss.fs = tss.gs = 0x10 | 0x3;
}
