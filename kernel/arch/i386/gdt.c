#include "gdt.h"

extern void load_seg_registers(uint32_t addr);
void set_gdt_entry(uint32_t entry, uint32_t base, uint32_t limit,
		   uint8_t access, uint8_t gran);

GdtEntry gdt[5];
GdtPtr gdt_ptr;

void init_gdt()
{
	gdt_ptr.limit = sizeof(gdt) - 1;
	gdt_ptr.base = (uint32_t)&gdt;

	set_gdt_entry(0, 0, 0, 0, 0); /* Null descriptor */
	set_gdt_entry(1, 0, 0xFFFFFFFF, 0x9A, 0xCF); /* Kernel code segment */
	set_gdt_entry(2, 0, 0xFFFFFFFF, 0x92, 0xCF); /* Kernel data segment */
	set_gdt_entry(3, 0, 0xFFFFFFFF, 0xFA, 0xCF); /* User code segment */
	set_gdt_entry(4, 0, 0xFFFFFFFF, 0xF2, 0xCF); /* User data segment */

	load_seg_registers((uint32_t)&gdt_ptr);
}

void set_gdt_entry(uint32_t entry, uint32_t base, uint32_t limit,
		   uint8_t access, uint8_t gran)
{
	gdt[entry].base_low = base & 0xFFFF;
	gdt[entry].base_middle = (base >> 16) & 0xFF;
	gdt[entry].base_high = (base >> 24) & 0xFF;
	gdt[entry].limit = limit & 0xFFFF;
	gdt[entry].flags = (limit >> 16) & 0xF;
	gdt[entry].flags |= gran & 0xF0;
	gdt[entry].access = access;
}
