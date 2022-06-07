cmake_minimum_required(VERSION 3.21.2)
project(libc)

set(CMAKE_ASM_NASM_OBJECT_FORMAT elf)
enable_language(ASM_NASM)



add_library(libc STATIC include/string.h include/sys/cdefs.h string/strlen.cpp)
target_include_directories(libc PUBLIC
        ${CMAKE_SOURCE_DIR}/libc/include
        ${CMAKE_SOURCE_DIR}/libc/include/string
        ${CMAKE_SOURCE_DIR}/libc/include/sys)
set_target_properties(libc PROPERTIES LINKER_LANGUAGE CXX)