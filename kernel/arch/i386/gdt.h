#ifndef _GDT_H
#define _GTD_H

#ifndef __ASSEMBLER__
#include <stdint.h>
#endif

#define SEG_KCODE (1 << 3)
#define SEG_KDATA (2 << 3)
#define SEG_UCODE (3 << 3)
#define SEG_UDATA (4 << 3)
#define SEG_TSS (5 << 3)

#ifndef __ASSEMBLER__
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

typedef struct {
	uint32_t link;
	uint32_t esp0;
	uint32_t ss0;
	uint32_t esp1;
	uint32_t ss1;
	uint32_t esp2;
	uint32_t ss2;
	uint32_t cr3;
	uint32_t eip;
	uint32_t eflags;
	uint32_t eax;
	uint32_t ecx;
	uint32_t edx;
	uint32_t ebx;
	uint32_t esp;
	uint32_t ebp;
	uint32_t esi;
	uint32_t edi;
	uint32_t es;
	uint32_t cs;
	uint32_t ss;
	uint32_t ds;
	uint32_t fs;
	uint32_t gs;
	uint32_t ldtr;
	uint32_t iopb;
	uint32_t ssp;
} __attribute__((packed)) TssEntry;

void init_gdt();
void write_tss(uint32_t num, uint16_t ss0, uint32_t esp0);

#endif // __ASSEMBLER__
#endif // _GDT_H
