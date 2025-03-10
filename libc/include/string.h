#ifndef _STRING_H
#define _STRING_H 1

#include <sys/cdefs.h>

#include <stddef.h>

int memcmp(const void* a, const void* b, size_t size);
void* memcpy(void* __restrict dest, const void* __restrict src, size_t size);
void* memmove(void* dest, const void* src, size_t size);
void* memset(void* dest, int val, size_t size);
size_t strlen(const char* str);

#endif

