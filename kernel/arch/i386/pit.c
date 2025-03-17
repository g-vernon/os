#include "idt.h"
#include "pit.h"

#include <stdint.h>
#include <stdio.h>

/* PIC mode masks -- see Intel 8253/8254 documentation */

/* 0b00 = channel 0, 0b01 = channel 1, 0b10 = channel 2, 0b11 = read-back command */
#define CHANNEL_SEL(x) ((x) << 6)

/* 0b00 = Latch count value command, 0b01 = lobyte only, 0b10 = hibyte only, 0b11 = lobyte/hibyte */
#define ACCESS_MODE(x) ((x) << 4)

/* 0b011 = mode 3 square wave generator */
#define OPERATING_MODE(x) ((x) << 1)

/* 0b0 = 16-bit binary, 0b1 = four-digit BCD */
#define BCD_MODE(x) (x)

#define PIC_CHN_0_DATA_ADDR 0x40
#define PIC_MODE_ADDR 0x43
#define TIMER_PIC_MODE                                                        \
	CHANNEL_SEL(0x0) | ACCESS_MODE(0x3) | OPERATING_MODE(0x3) | \
		BCD_MODE(0x0)

uint64_t ticks;
const uint32_t freq = 19; /* Units of Hz, minimum is 19 Hz */

void on_irq0(InterruptRegisters *regs)
{
	ticks += 1;
}

void init_timer()
{
	ticks = 0;
	irq_install_handler(0, &on_irq0);

	const uint32_t divisor = 1193182 / freq;
	_Static_assert(divisor < 65536, "Divisor out of bounds");

	outb(PIC_MODE_ADDR, TIMER_PIC_MODE);
	outb(PIC_CHN_0_DATA_ADDR, (uint8_t)(divisor & 0xFF));
	outb(PIC_CHN_0_DATA_ADDR, (uint8_t)((divisor >> 8) & 0xFF));
}
