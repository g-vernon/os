#include <kernel/tty.h>

void kernel_main(void)
{
	/* Initialize terminal interface */
	terminal_initialize();
	terminal_writestring("Hello, kernelspace! \n");
	terminal_writestring("These violent delights have violent ends \n");
}
