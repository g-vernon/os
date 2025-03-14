#include <string.h>

void *memset(void *usr_ptr, int value, size_t size)
{
	unsigned char *dst = (unsigned char *)usr_ptr;
	for (size_t i = 0; i < size; i++)
		dst[i] = (unsigned char)value;
	return usr_ptr;
}
