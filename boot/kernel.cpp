#include <stdint.h>
#include "multiboot2.h"

void write_string( int colour, const char *string )
{
    volatile char *video = (volatile char*)0xB8000;
    while( *string != 0 )
    {
        *video++ = *string++;
        *video++ = colour;
    }
}

extern "C" void kernel_main(unsigned long mbi_addr) {
    auto addr = mbi_addr;

    write_string(0x07, "Hello, Kernel!                       ");
    for (auto tag = (struct multiboot_tag *) ((uint8_t *) addr + 8);
         tag->type != MULTIBOOT_TAG_TYPE_END;
         tag = (struct multiboot_tag *) ((multiboot_uint8_t *) tag + ((tag->size + 7) & ~7))) {

        switch (tag->type) {

        }
    }
}