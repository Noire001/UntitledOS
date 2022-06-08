#include <stddef.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>

static bool print(const char *data, size_t length) {
    const auto *bytes = (const unsigned char *) data;
    for (size_t i = 0; i < length; i++) {
        if (putchar(bytes[i]) == EOF) {
            return false;
        }
    }
    return true;
}

int printf(const char *format, ...) {
    va_list args;
    va_start(args, format);
    int written = 0;

    while (*format != '\0') {
        size_t max_remaining = 2147483647 - written;

        if (format[0] != '%' || format[1] == '%') {
            if (format[0] == '%') {
                format++;
            }
            size_t amount = 1;
            while (format[amount] && format[amount] != '%') {
                amount++;
            }
            if (max_remaining < amount) {
                return -1;
            }
            if (!print(format, amount)) {
                return -1;
            }
            written += (int) amount;
            format += amount;
        }

        const char *format_begun_at = format++;

        if (*format == 'c') {
            format++;
            char c = (char) va_arg(args, int);
            if (!max_remaining) {
                return -1;
            }
            if (!print(&c, sizeof(c))) {
                return -1;
            }
            written++;
        } else if (*format == 's') {
            format++;
            const char *str = va_arg(args, const char*);
            if (!max_remaining) {
                return -1;
            }
            if (!print(str, strlen(str))) {
                return -1;
            }
            written++;
        } else {
            format = format_begun_at;
            size_t length = strlen(format);
            if (max_remaining < length) {
                return -1;
            }
            if (!print(format, length)) {
                return -1;
            }
            written++;
            format++;
        }

    }
    va_end(args);
    return written;
}