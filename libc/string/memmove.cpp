#include <stddef.h>
#include <string.h>

void* memmove(void* destination_pointer, const void* source_pointer, size_t size) {
    if (destination_pointer == source_pointer) {
        return destination_pointer;
    }
    if (destination_pointer < source_pointer) {
        return memcpy(destination_pointer, source_pointer, size);
    }
    auto* destination = (unsigned char*) destination_pointer;
    auto* source = (unsigned char*) source_pointer;
    for (size_t i = 0; i < size; i++) {
        destination[size - i - 1] = source[size - i - 1];
    }
    return destination_pointer;
}