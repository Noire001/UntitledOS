cmake_minimum_required(VERSION 3.21.2)

project(UntitledOS)
## Setup cross-compilation
set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_SYSTEM_PROCESSOR x86_64)
set(ARCH x86_64)

ENABLE_LANGUAGE(ASM_NASM)
set(CMAKE_ASM_NASM_COMPILER /usr/bin/nasm)
set(CMAKE_ASM_NASM_LINK_EXECUTABLE "ld <CMAKE_ASM_NASM_LINK_FLAGS> <LINK_FLAGS> <OBJECTS>  -o <TARGET> <LINK_LIBRARIES> ")
set(CMAKE_ASM_NASM_OBJECT_FORMAT elf64)

set(TOOLS $ENV{HOME}/opt/cross)
set(OUT ${CMAKE_SOURCE_DIR}/build/${ARCH})

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_C_STANDARD 17)
set(CMAKE_C_COMPILER ${TOOLS}/bin/x86_64-elf-gcc)
set(CMAKE_CXX_COMPILER ${TOOLS}/bin/x86_64-elf-g++)

set(CMAKE_CXX_FLAGS "-ffreestanding -O2 -Wall -Wextra -fno-exceptions -fno-rtti")
set(CMAKE_C_FLAGS "-ffreestanding -O2 -Wall -Wextra")

set(KERNEL_BIN "UntitledOS.bin")
set(KERNEL_ISO ${CMAKE_PROJECT_NAME}.iso)

add_custom_target(build-time-make-directory ALL
        COMMAND ${CMAKE_COMMAND} -E make_directory ${OUT}/kernel)
add_executable(${KERNEL_BIN} boot/multiboot_header.asm boot/boot.asm boot/long_mode_init.asm)
set_target_properties(${KERNEL_BIN} PROPERTIES LINK_FLAGS "-n -T ${CMAKE_SOURCE_DIR}/boot/linker.ld"
        RUNTIME_OUTPUT_DIRECTORY "${OUT}/kernel"
        LIBRARY_OUTPUT_DIRECTORY "${OUT}/kernel"
        RUNTIME_OUTPUT_DIRECTORY "${OUT}/kernel")


add_custom_target(${KERNEL_ISO} ALL
        COMMAND ${CMAKE_SOURCE_DIR}/generate-iso.sh ${CMAKE_SOURCE_DIR}
        COMMENT "Making .iso file"
        BYPRODUCTS ${KERNEL_iso}
        RUNTIME_OUTPUT_DIRECTORY "${OUT}")
add_dependencies(${KERNEL_ISO} ${KERNEL_BIN})
