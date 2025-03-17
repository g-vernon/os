#include <limits.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

static bool print(const char *data, size_t length)
{
	const unsigned char *bytes = (const unsigned char *)data;
	for (size_t i = 0; i < length; i++) {
		if (putchar(bytes[i]) == EOF)
			return false;
	}
	return true;
}

int printf(const char *restrict format, ...)
{
	va_list parameters;
	va_start(parameters, format);

	int written = 0;

	while (*format != '\0') {
		size_t max_remaining = INT_MAX - written;

		/* Not a format character */
		if (format[0] != '%' || format[1] == '%') {
			if (format[0] == '%')
				format++;
			size_t amount = 1;
			while (format[amount] && format[amount] != '%')
				amount++;

			if (max_remaining < amount) {
				/* TODO: Set errno to EOVERFLOW */
				return -1;
			}
			if (!print(format, amount))
				return -1;
			format += amount;
			written += amount;
			continue;
		}

		/* We are formatting */
		const char *format_begun_at = format++;

		switch (*format) {
		case 'c': {
			format++;
			char c = (char)va_arg(parameters, int);
			if (!max_remaining) {
				/* TODO: Set errno to EOVERFLOW */
				return -1;
			}
			if (!print(&c, sizeof(c)))
				return -1;
			written++;
			break;
		}
		case 'd': {
			format++;
			int num = va_arg(parameters, int);
			size_t len = 0;
			char num_str[11];

			if (num < 0) {
				if (!max_remaining) {
					/* TODO: Set errno to EOVERFLOW */
					return -1;
				}
				num = -num;
				if (!print("-", sizeof(char)))
					return -1;
				written++;
				max_remaining--;
			}

			do {
				num_str[len++] = (num % 10) + 48;
			} while (num /= 10);

			while (len) {
				if (!max_remaining) {
					/* TODO: Set errno to EOVERFLOW */
					return -1;
				}
				if (!print(&num_str[--len], sizeof(char)))
					return -1;
				written++;
				max_remaining--;
			}
			break;
		}
		case 's': {
			format++;
			const char *str = va_arg(parameters, const char *);
			size_t len = strlen(str);
			if (max_remaining < len) {
				/* TODO: Set errno to EOVERFLOW */
				return -1;
			}
			if (!print(str, len)) {
				return -1;
			}
			written += len;
			break;
		}
		default: {
			format = format_begun_at;
			size_t len = strlen(format);
			if (max_remaining < len) {
				/* TODO: Set errno to EOVERFLOW. */
				return -1;
			}
			if (!print(format, len))
				return -1;
			written += len;
			format += len;
			break;
		}
		}
	}
	va_end(parameters);
	return (written);
}
