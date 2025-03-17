#ifndef _IDT_H
#define _IDT_H

#include <stdint.h>

typedef struct {
	uint16_t offset_low;
	uint16_t sel; /* Segment selector to load before calling ISR */
	uint8_t reserved;
	uint8_t flags;
	uint16_t offset_high;
} __attribute__((packed)) IdtEntry;

typedef struct {
	uint16_t limit;
	uint32_t base;
} __attribute__((packed)) IdtPtr;

typedef struct {
	/* Additional registers we want to save */
	uint32_t cr2;
	uint32_t ds;
	/* General purpose registers (pusha) */
	uint32_t edi;
	uint32_t esi;
	uint32_t ebp;
	uint32_t esp;
	uint32_t ebx;
	uint32_t edx;
	uint32_t ecx;
	uint32_t eax;
	/* Defined by x86 - see
	 * Intel 64 & IA-32 SDM vol 3 section 6.8.5 Stack Switching */
	uint32_t int_no;
	uint32_t err_code;
	uint32_t eip;
	uint32_t csm;
	uint32_t eflags;
	/* As above, used when changing ring levels */
	uint32_t useresp;
	uint32_t ss;
} __attribute__((packed)) InterruptRegisters;

void init_idt();
void irq_install_handler(int irq, void (*handler)(InterruptRegisters *regs));
void outb(uint16_t port, uint8_t data);

#endif // _IDT_H
