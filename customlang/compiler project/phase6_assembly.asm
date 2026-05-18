; ============================================
; Phase 6 — Generated Assembly (x86 NASM)
; CustomLang Compiler
; Source: phase5_optimized.txt
; ============================================

section .data
    fmt db "%d", 10, 0   ; printf format string
    str0 db "--- Datatypes & Loops ---", 10, 0
    str1 db "Starting repeat loop...", 10, 0
    str2 db "Loop iteration:", 10, 0
    str3 db "Loop finished successfully!", 10, 0
    count           dd 0
    pi_approx       dd 0
    letter          dd 0
    body            dd 0

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
    ; print_str "--- Datatypes & Loops ---"
    lea rcx, [rel str0]
    call printf
    ; count = 1
    mov eax, 1
    mov [rel count], eax
    ; pi_approx = 3
    mov eax, 3
    mov [rel pi_approx], eax
    ; letter = 65
    mov eax, 65
    mov [rel letter], eax
    ; print_str "Starting repeat loop..."
    lea rcx, [rel str1]
    call printf
    ; print_str "Loop iteration:"
    lea rcx, [rel str2]
    call printf
    ; print 1
    mov eax, 1
    lea rcx, [rel fmt]
    mov edx, eax
    call printf
    ; /* ELIMINATED: t0 = 2  /* folded: 1 + 1 */ */
    ; count = 2
    mov eax, 2
    mov [rel count], eax
L0:
    mov eax, 1
    cmp eax, 0
    je L1
    ; body = 1390693504
    mov eax, 1390693504
    mov [rel body], eax
L1:
    ; print_str "Loop finished successfully!"
    lea rcx, [rel str3]
    call printf
    ; ─────────────────────────────────────────

    ; ── function epilogue ──
    add  rsp, 32
    pop  rbp
    mov  eax, 0
    ret
