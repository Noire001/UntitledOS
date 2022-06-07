cmake_minimum_required(VERSION 3.21.2)
project(kernel)




add_library(kernel STATIC arch/x86_64/multiboot_header.asm arch/x86_64/boot.asm arch/x86_64/long_mode_init.asm kernel/kernel.cpp arch/x86_64/multiboot2.h include/kernel/tty.h arch/x86_64/tty.cpp arch/x86_64/vga.h)
target_include_directories(kernel PUBLIC
        ${CMAKE_SOURCE_DIR}/libc/include
        ${CMAKE_SOURCE_DIR}/libc/include/string
        ${CMAKE_SOURCE_DIR}/libc/include/sys
        ${CMAKE_SOURCE_DIR}/kernel)

set_target_properties(kernel PROPERTIES LINKER_LANGUAGE CXX)
