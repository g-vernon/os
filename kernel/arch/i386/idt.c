#include "idt.h"

#include "gdt.h"
#include "vga.h"

#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define NUM_EXCEPTIONS 32
#define NUM_IRQ 16

/* PIC addresses */
#define PIC_MASTER_COMMAND 0x20
#define PIC_MASTER_DATA 0x21
#define PIC_SLAVE_COMMAND 0xA0
#define PIC_SLAVE_DATA 0XA1

/* PIC commands */
#define PIC_INITIALISE 0x11

/* Present = 1, DPL = 00, reserved bit = 0, gate type E = 32-bit interrupt gate */
#define GATE_FLAGS 0x8E

extern void isr0();
extern void isr1();
extern void isr2();
extern void isr3();
extern void isr4();
extern void isr5();
extern void isr6();
extern void isr7();
extern void isr8();
extern void isr9();
extern void isr10();
extern void isr11();
extern void isr12();
extern void isr13();
extern void isr14();
extern void isr15();
extern void isr16();
extern void isr17();
extern void isr18();
extern void isr19();
extern void isr20();
extern void isr21();
extern void isr22();
extern void isr23();
extern void isr24();
extern void isr25();
extern void isr26();
extern void isr27();
extern void isr28();
extern void isr29();
extern void isr30();
extern void isr31();

extern void isr128();
extern void isr177();

extern void irq0();
extern void irq1();
extern void irq2();
extern void irq3();
extern void irq4();
extern void irq5();
extern void irq6();
extern void irq7();
extern void irq8();
extern void irq9();
extern void irq10();
extern void irq11();
extern void irq12();
extern void irq13();
extern void irq14();
extern void irq15();

extern void load_idt_gates(uint32_t);
void set_idt_gate(uint8_t gate, uint32_t base, uint16_t sel, uint8_t flag);

__attribute__((aligned(0x10))) IdtEntry idt[256];
IdtPtr idt_ptr;

void outb(uint16_t port, uint8_t data)
{
	/*
	 * These gcc extended asm constraints are specific to the i386 family
	 * N = unsigned 8-bit integer
	 * a = use the a register
	 * d = use the d register
	 */
	asm volatile("outb %0, %1" : : "a"(data), "Nd"(port));
}

void init_idt()
{
	idt_ptr.limit = sizeof(idt) - 1;
	idt_ptr.base = (uint32_t)&idt;
	memset(&idt, 0, sizeof(idt));

	/* Kick PIC chips into initialisation mode -- they will wait
	 * for three "initialisation command words" */
	outb(PIC_MASTER_COMMAND, PIC_INITIALISE);
	outb(PIC_SLAVE_COMMAND, PIC_INITIALISE);

	/* Setup vector offsets */
	outb(PIC_MASTER_DATA, 0x20);
	outb(PIC_SLAVE_DATA, 0x28);

	/* Tell master PIC there is a slave PIC at IRQ2 */
	outb(PIC_MASTER_DATA, 0x04);
	/* Tell slave PIC its cascade identity */
	outb(PIC_SLAVE_DATA, 0x02);

	/* Configure PICS to use 8086/88 mode */
	outb(PIC_MASTER_DATA, 0x01);
	outb(PIC_SLAVE_DATA, 0x01);

	/* Chips now ready to receive interrupt requests.
	 * Reset interrupt mask to enable all IRQ channels. */
	outb(PIC_MASTER_DATA, 0x0);
	outb(PIC_SLAVE_DATA, 0x0);

	/* Interrupts */
	set_idt_gate(0, (uint32_t)isr0, SEG_KCODE, GATE_FLAGS);
	set_idt_gate(1, (uint32_t)isr1, SEG_KCODE, GATE_FLAGS);
	set_idt_gate(2, (uint32_t)isr2, SEG_KCODE, GATE_FLAGS);
	set_idt_gate(3, (uint32_t)isr3, SEG_KCODE, GATE_FLAGS);
	set_idt_gate(4, (uint32_t)isr4, SEG_KCODE, GATE_FLAGS);
	set_idt_gate(5, (uint32_t)isr5, SEG_KCODE, GATE_FLAGS);
	set_idt_gate(6, (uint32_t)isr6, SEG_KCODE, GATE_FLAGS);
	set_idt_gate(7, (uint32_t)isr7, SEG_KCODE, GATE_FLAGS);
	set_idt_gate(8, (uint32_t)isr8, SEG_KCODE, GATE_FLAGS);
	set_idt_gate(9, (uint32_t)isr9, SEG_KCODE, GATE_FLAGS);
	set_idt_gate(10, (uint32_t)isr10, SEG_KCODE, GATE_FLAGS);
	set_idt_gate(11, (uint32_t)isr11, SEG_KCODE, GATE_FLAGS);
	set_idt_gate(12, (uint32_t)isr12, SEG_KCODE, GATE_FLAGS);
	set_idt_gate(13, (uint32_t)isr13, SEG_KCODE, GATE_FLAGS);
	set_idt_gate(14, (uint32_t)isr14, SEG_KCODE, GATE_FLAGS);
	set_idt_gate(15, (uint32_t)isr15, SEG_KCODE, GATE_FLAGS);
	set_idt_gate(16, (uint32_t)isr16, SEG_KCODE, GATE_FLAGS);
	set_idt_gate(17, (uint32_t)isr17, SEG_KCODE, GATE_FLAGS);
	set_idt_gate(18, (uint32_t)isr18, SEG_KCODE, GATE_FLAGS);
	set_idt_gate(19, (uint32_t)isr19, SEG_KCODE, GATE_FLAGS);
	set_idt_gate(20, (uint32_t)isr20, SEG_KCODE, GATE_FLAGS);
	set_idt_gate(21, (uint32_t)isr21, SEG_KCODE, GATE_FLAGS);
	set_idt_gate(22, (uint32_t)isr22, SEG_KCODE, GATE_FLAGS);
	set_idt_gate(23, (uint32_t)isr23, SEG_KCODE, GATE_FLAGS);
	set_idt_gate(24, (uint32_t)isr24, SEG_KCODE, GATE_FLAGS);
	set_idt_gate(25, (uint32_t)isr25, SEG_KCODE, GATE_FLAGS);
	set_idt_gate(26, (uint32_t)isr26, SEG_KCODE, GATE_FLAGS);
	set_idt_gate(27, (uint32_t)isr27, SEG_KCODE, GATE_FLAGS);
	set_idt_gate(28, (uint32_t)isr28, SEG_KCODE, GATE_FLAGS);
	set_idt_gate(29, (uint32_t)isr29, SEG_KCODE, GATE_FLAGS);
	set_idt_gate(30, (uint32_t)isr30, SEG_KCODE, GATE_FLAGS);
	set_idt_gate(31, (uint32_t)isr31, SEG_KCODE, GATE_FLAGS);
	/* IRQs */
	set_idt_gate(32, (uint32_t)irq0, SEG_KCODE, GATE_FLAGS);
	set_idt_gate(33, (uint32_t)irq0, SEG_KCODE, GATE_FLAGS);
	set_idt_gate(34, (uint32_t)irq0, SEG_KCODE, GATE_FLAGS);
	set_idt_gate(35, (uint32_t)irq0, SEG_KCODE, GATE_FLAGS);
	set_idt_gate(36, (uint32_t)irq0, SEG_KCODE, GATE_FLAGS);
	set_idt_gate(37, (uint32_t)irq0, SEG_KCODE, GATE_FLAGS);
	set_idt_gate(38, (uint32_t)irq0, SEG_KCODE, GATE_FLAGS);
	set_idt_gate(39, (uint32_t)irq0, SEG_KCODE, GATE_FLAGS);
	set_idt_gate(40, (uint32_t)irq0, SEG_KCODE, GATE_FLAGS);
	set_idt_gate(41, (uint32_t)irq0, SEG_KCODE, GATE_FLAGS);
	set_idt_gate(42, (uint32_t)irq0, SEG_KCODE, GATE_FLAGS);
	set_idt_gate(43, (uint32_t)irq0, SEG_KCODE, GATE_FLAGS);
	set_idt_gate(44, (uint32_t)irq0, SEG_KCODE, GATE_FLAGS);
	set_idt_gate(45, (uint32_t)irq0, SEG_KCODE, GATE_FLAGS);
	set_idt_gate(46, (uint32_t)irq0, SEG_KCODE, GATE_FLAGS);
	set_idt_gate(47, (uint32_t)irq0, SEG_KCODE, GATE_FLAGS);
	/* System calls */
	set_idt_gate(128, (uint32_t)isr128, SEG_KCODE, GATE_FLAGS);
	set_idt_gate(177, (uint32_t)isr177, SEG_KCODE, GATE_FLAGS);

	load_idt_gates((uint32_t)&idt_ptr);
}

void set_idt_gate(uint8_t gate, uint32_t offset, uint16_t sel, uint8_t flag)
{
	idt[gate].offset_low = offset & 0xFFFF;
	idt[gate].offset_high = (offset >> 16) & 0xFFFF;
	idt[gate].sel = sel;
	idt[gate].reserved = 0;
	idt[gate].flags = flag | 0x60;
}

char *exception_messages[NUM_EXCEPTIONS] = {
	"Division by zero",
	"Single-step interrupt",
	"Non-maskable interrupt",
	"Breakpoint",
	"Overflow",
	"Out of bounds",
	"Invalid opcode",
	"Coprocessor not available",
	"Double fault",
	"Coprocessor segment overrun",
	"Invalid TSS",
	"Segment not present",
	"Stack-segment fault",
	"General protection fault",
	"Page fault",
	"Reserved",
	"x87 floating-point exception",
	"Alignment check",
	"Machine check",
	"SIMD floating-point exception",
	"Virtualisation exception",
	"Control protection exception",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Hypervisor injection exception",
	"VMM communication exception",
	"Security exception",
	"Reserved",
};

void exception_handler(InterruptRegisters *regs)
{
	if (regs->int_no < NUM_EXCEPTIONS) {
		printf("%s \n", exception_messages[regs->int_no]);
		printf("Exception! System halted \n");
		for (;;)
			;
	}
}

void *irq_routines[NUM_IRQ] = {
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
};

void irq_install_handler(int irq, void (*handler)(InterruptRegisters *regs))
{
	irq_routines[irq] = handler;
	printf("Installed irq handler %d at %d \n", irq, handler);
}

void irq_uninstall_handler(int irq)
{
	irq_routines[irq] = 0;
}

void irq_handler(InterruptRegisters *regs)
{
	void (*handler)(InterruptRegisters *regs);
	handler = irq_routines[regs->int_no - NUM_EXCEPTIONS];

	if (handler) {
		handler(regs);
	}

	if (regs->int_no >= 40) {
		outb(0xA0, 0x20);
	}

	outb(0x20, 0x20);
}
