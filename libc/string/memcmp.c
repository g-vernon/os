#include <string.h>

int memcmp(const void* usr_a, const void* usr_b, size_t size)
{
	const unsigned char* a = (const unsigned char*) usr_a;
	const unsigned char* b = (const unsigned char*) usr_b;
	for (size_t i = 0; i < size; i++)
	{
		if (a[i] < b[i])
			return -1;
		if (b[i] < a[i])
			return 1;
	}
	return 0;
}
