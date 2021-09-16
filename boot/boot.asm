global start

section .text
bits 32
start:
    mov esp, stack_top
    call check_multiboot
    call check_cpuid
    call check_long_mode

    ; print `OK` to screen
    mov dword [0xb8000], 0x2f4b2f4f
    hlt

error:
    mov dword [0xb8000], 0x4f524f45
    mov dword [0xb8004], 0x4f3a4f52
    mov dword [0xb8008], 0x4f204f20
    mov byte  [0xb800a], al
    hlt

check_multiboot:
    cmp eax, 0x36d76289
    jne .no_multiboot
    ret

.no_multiboot:
    mov al, "0"
    jmp error

check_cpuid:
    pushfd
    pop eax

    mov ecx, eax
    xor eax, 1 << 21

    push eax
    popfd

    pushfd
    pop eax

    push ecx
    popfd

    cmp eax,ecx
    je .no_cpuid
    ret

.no_cpuid:
    mov al, "1"
    jmp error

check_long_mode:
    mov eax, 0x80000000
    cpuid
    cmp eax, 0x80000001
    jb .no_long_mode

    mov eax, 0x80000001
    cpuid
    test edx, 1 << 29
    jz .no_long_mode
    ret

.no_long_mode:
    mov al, "2"
    jmp error



section .bss
stack_bottom:
    resb 64

stack_top:

