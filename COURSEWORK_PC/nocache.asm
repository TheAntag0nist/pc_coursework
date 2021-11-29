section .text

global _off_cache
global _on_cache

_off_cache:
; Begin frame
    push rbp
    mov rbp, rsp
    push rax
    push rbx
    push rdx
    push rcx

    ;Step 1 - Disable the caches
    mov rax, cr0
    or rax, 1<<30
    mov cr0, rax

; For some models we need to invalidated the L1I
; write to mem
    wbinvd

; Step 2 - Disable speculative accesses
    xor rax, rax
    xor rdx, rdx
    mov ecx, 2FFH  ;MSR number is 2FFH
    wrmsr

; End frame
    pop rcx
    pop rdx
    pop rbx
    pop rax
    mov rsp, rbp
    pop rbp
ret
;===============================================================
_on_cache:
; Begin frame
    push rbp
    mov rbp, rsp
    push rax
    push rbx
    push rdx
    push rcx

;Step 1 - On the caches
    mov rax, cr0
    or rax, 1<<30
    mov cr0, rax

; For some models we need to invalidated the L1I
; write to mem
    wbinvd

; Step 2 - On speculative accesses
    xor rax, rax
    xor rdx, rdx
    mov ecx, 0x2FFH  ;MSR number is 2FFH
    wrmsr

; End frame
    pop rcx
    pop rdx
    pop rbx
    pop rax
    mov rsp, rbp
    pop rbp
ret