; ============================================
; Phase 6 — Generated Assembly (x86 NASM)
; CustomLang Compiler
; Source: phase5_optimized.txt
; ============================================

section .data
    fmt db "%d", 10, 0   ; printf format string
    x               dd 0
    take_input      dd 0
    y               dd 0
    result          dd 0

section .bss
    ; (reserved for future use)

section .text
    global main
    extern printf

main:
    ; ── function prologue ──
    push rbp
    mov  rbp, rsp
    sub  rsp, 32

    ; ─────────────────────────────────────────
    ; x = 75 /* take_input
    mov eax, 75
    mov [rel x], eax
    ; y = 50 /* take_input
    mov eax, 50
    mov [rel y], eax
    ; /* ELIMINATED: t0 = 125  /* folded: 75 + 50 */ */
    ; result = 125
    mov eax, 125
    mov [rel result], eax
    ; print 125
    mov eax, 125
    lea rcx, [rel fmt]
    mov edx, eax
    call printf
    mov eax, 1
    cmp eax, 0
    jne L0
    jmp L1
L0:
    ; print 1
    mov eax, 1
    lea rcx, [rel fmt]
    mov edx, eax
    call printf
    jmp L2
L1:
    mov eax, 0
    cmp eax, 0
    jne L3
    jmp L4
L3:
    ; print 0
    mov eax, 0
    lea rcx, [rel fmt]
    mov edx, eax
    call printf
    jmp L2
L4:
    ; print 2
    mov eax, 2
    lea rcx, [rel fmt]
    mov edx, eax
    call printf
L2:
    ; ─────────────────────────────────────────

    ; ── function epilogue ──
    add  rsp, 32
    pop  rbp
    mov  eax, 0
    ret
