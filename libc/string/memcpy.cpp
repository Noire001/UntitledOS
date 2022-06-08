#include <stddef.h>
#include <string.h>

void *memcpy(void *destination, const void *source, size_t size) {
    volatile auto *d = (unsigned char *) destination;
    volatile auto *s = (unsigned char *) source;
    for (size_t i = 0; i < size; i++) {
        d[i] = s[i];
    }
    return destination;
}