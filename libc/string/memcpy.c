#include <string.h>

void* memcpy(void* restrict usr_dst, const void* restrict usr_src, size_t size)
{
	unsigned char* dst = (unsigned char*) usr_dst;
	const unsigned char* src = (const unsigned char*) usr_src;
	for (size_t i = 0; i < size; i++)
		dst[i] = src[i];
	return usr_dst;
}
