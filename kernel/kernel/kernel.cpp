#include <stdint.h>
#include "../arch/x86_64/multiboot2.h"
#include "../include/kernel/tty.h"
#include "stdio.h"


extern "C" void kernel_main(unsigned long mbi_addr) {
    terminal_initialize();
    auto addr = mbi_addr;
    for (int i = 0; i <  5000; i++) {
        printf("Hello, kernel World! %d", i);
    }

    for (auto tag = (struct multiboot_tag *) ((uint8_t *) addr + 8);
         tag->type != MULTIBOOT_TAG_TYPE_END;
         tag = (struct multiboot_tag *) ((multiboot_uint8_t *) tag + ((tag->size + 7) & ~7))) {

        switch (tag->type) {
            //we will parse multiboot2 struct tags here
        }
    }
}