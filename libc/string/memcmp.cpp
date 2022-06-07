#include <string.h>

int memcmp(const void* s1, const void* s2, size_t size) {
    const auto* a = (const unsigned char*) s1;
    const auto* b = (const unsigned char*) s2;
    for (size_t i = 0; i < size; i++) {
        if (a[i]  > b[i]) {
            return 1;
        } else if (a[i] < b[i]) {
            return -1;
        }
    }
    return 0;
}