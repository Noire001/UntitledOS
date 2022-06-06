global start
extern long_mode_start
section .text
bits 32
start:
    mov esp, stack_top
    mov edi, ebx    ; move Multiboot info pointer to edi
    call check_multiboot
    call check_cpuid
    call check_long_mode
    call map_pml4_pdp
    call enable_paging

    lgdt [gdt64.pointer]
    jmp gdt64.code:long_mode_start
    ; print `OK` to screen
    mov dword [0xb8000], 0x2f4b2f4f
    hlt

map_pml4_pdp:
    mov eax, p3_table
    or eax, 0b11
    mov [p4_table], eax

    mov eax, p2_table
    or eax, 0b11
    mov [p3_table], eax
    mov ecx, 0

.map_pd:
    mov eax, 0x200000
    mul ecx
    or eax, 0b10000011
    mov [p2_table + ecx * 8], eax

    inc ecx
    cmp ecx, 512

    ret

enable_paging:
    mov eax, p4_table
    mov cr3, eax ;mov into cr registers is only possible from another register

    mov eax, cr4
    or eax, 1 << 5
    mov cr4, eax

    mov ecx, 0xC0000080
    rdmsr
    or eax, 1 << 8
    wrmsr

    mov eax, cr0
    or eax, 1 << 31
    mov cr0,eax

    ret

;print ERR and a number on screen
error:
    mov dword [0xb8000], 0x4f524f45
    mov dword [0xb8004], 0x4f3a4f52
    mov dword [0xb8008], 0x4f204f20
    mov byte  [0xb800a], al
    hlt

;check if kernel was loaded by multiboot using the magic number
check_multiboot:
    cmp eax, 0x36d76289
    jne .no_multiboot
    ret

.no_multiboot:
    mov al, "0"
    jmp error

;check if CPU supports CPUID
check_cpuid:
    ;get EFLAGS into stack then into eax
    pushfd
    pop eax
    ;copy eax to ecx and flip the 21st bit in eax (cpuid bit)
    mov ecx, eax
    xor eax, 1 << 21
    ;get eax into stack then into EFLAGS
    push eax
    popfd
    ;get EFLAGS into stack then into eax again
    pushfd
    pop eax
    ;get ecx into stack then into EFLAGS (original EFLAGS)
    push ecx
    popfd
    ;compare eax to ecx. the 21st eax bit should be flipped.
    cmp eax,ecx
    je .no_cpuid
    ret

.no_cpuid:
    mov al, "1"
    jmp error

check_long_mode:
    ;check if CPUID supports 0x80000001, required to check for long mode
    mov eax, 0x80000000
    cpuid
    cmp eax, 0x80000001
    jb .no_long_mode
    ;check for long mode, which is when bit 29 is set
    mov eax, 0x80000001
    cpuid
    test edx, 1 << 29
    jz .no_long_mode
    ret

.no_long_mode:
    mov al, "2"
    jmp error


section .bss
align 4096
;paging
p4_table:
    resb 4096
p3_table:
    resb 4096
p2_table:
    resb 4096

stack_bottom:
    resb 4096 * 4
stack_top:

section .rodata
gdt64:
    dq 0
.code: equ $ - gdt64
    dq (1<<43) | (1<<44) | (1<<47) | (1<<53)
.pointer:
    dw $ - gdt64 - 1
    dq gdt64