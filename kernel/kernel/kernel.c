#include <kernel/tty.h>

#include <stdio.h>

void kernel_main(void)
{
	/* Initialize terminal interface */
	terminal_initialize();
	printf("Hello, kernelspace! \n");
	printf("These violent delights have violent ends \n");
}
