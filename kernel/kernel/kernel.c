#include <kernel/tty.h>
#include <stdio.h>

#include "../drivers/ps2_kbd.h"

void kernel_main(void)
{
	/* Initialize terminal interface */
	terminal_initialize();
	init_keyboard();
	printf("Hello, kernelspace! \n");
	printf("These violent delights have violent ends \n");
	for(;;);
}
