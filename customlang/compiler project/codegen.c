/*
 * Phase 6 — Code Generator
 * Reads phase5_optimized.txt
 * Writes phase6_assembly.asm (x86 NASM assembly)
 *
 * Supports:
 *   - Variable assignment:     x = 5
 *   - Arithmetic TAC:          t0 = a + b  (+ - * /)
 *   - Print statement:         print 5
 *   - If goto labels:          if 1 goto L0
 *   - Goto statements:         goto L1
 *   - Labels:                  L0:
 *   - Loop body:               body = N
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LINES  1000
#define MAX_LEN    256
#define MAX_VARS   200

/* ── Variable registry ── */
char var_names[MAX_VARS][64];
int  var_count = 0;

char str_literals[MAX_VARS][256];
int  str_count = 0;

int var_exists(const char *name) {
    for(int i = 0; i < var_count; i++)
        if(strcmp(var_names[i], name) == 0) return 1;
    return 0;
}

void register_var(const char *name) {
    if(!var_exists(name)) {
        strcpy(var_names[var_count++], name);
    }
}

/* ── Helpers ── */
int is_number(const char *s) {
    if(!s || !*s) return 0;
    int i = 0;
    if(s[0] == '-') i = 1;
    for(; s[i]; i++)
        if(!isdigit((unsigned char)s[i])) return 0;
    return 1;
}

int is_label(const char *s) {
    /* L0: L1: etc */
    return s[0] == 'L' && isdigit((unsigned char)s[1]);
}

int is_temp(const char *s) {
    return s[0] == 't' && isdigit((unsigned char)s[1]);
}

/* load value into eax — either immediate or memory */
void load_eax(FILE *out, const char *operand) {
    if(is_number(operand))
        fprintf(out, "    mov eax, %s\n", operand);
    else
        fprintf(out, "    mov eax, [rel %s]\n", operand);
}

/* ── First pass: collect all variable names ── */
void collect_vars(char lines[][MAX_LEN], int count) {
    int in_after = 0;
    for(int i = 0; i < count; i++) {
        if(strstr(lines[i], "AFTER OPTIMIZATION:")) { in_after = 1; continue; }
        if(strstr(lines[i], "OPTIMIZATION SUMMARY:")) { in_after = 0; break; }
        if(!in_after) continue;

        char result[64], a[64], op[8], b[64];
        char str_val[256];

        if(sscanf(lines[i], "print_str %[^\n]", str_val) == 1) {
            int exists = 0;
            for(int k=0; k<str_count; k++) {
                if(strcmp(str_literals[k], str_val) == 0) exists = 1;
            }
            if(!exists) strcpy(str_literals[str_count++], str_val);
            continue;
        }

        /* result = a op b */
        if(sscanf(lines[i], "%63s = %63s %7s %63s", result, a, op, b) == 4) {
            register_var(result);
            if(!is_number(a) && !is_label(a)) register_var(a);
            if(!is_number(b) && !is_label(b)) register_var(b);
        }
        /* result = a */
        else if(sscanf(lines[i], "%63s = %63s", result, a) == 2) {
            /* skip lines like ELIMINATED or comments */
            if(result[0] == '/' || result[0] == '=') continue;
            register_var(result);
            if(!is_number(a) && !is_label(a)) register_var(a);
        }
    }
}

/* ── Second pass: generate assembly ── */
void generate_asm(char lines[][MAX_LEN], int count, FILE *out) {
    int in_after = 0;
    for(int i = 0; i < count; i++) {
        char *line = lines[i];

        if(strstr(line, "AFTER OPTIMIZATION:")) { in_after = 1; continue; }
        if(strstr(line, "OPTIMIZATION SUMMARY:")) { in_after = 0; break; }
        if(!in_after) continue;

        /* skip header/comment/empty/eliminated lines */
        if(line[0] == '\0') continue;
        if(line[0] == '=')  continue;
        if(line[0] == '-')  continue;
        if(strncmp(line, "/*", 2) == 0) {
            fprintf(out, "    ; %s\n", line);
            continue;
        }

        /* ── Label:  L0: ── */
        char label[64];
        if(sscanf(line, "%63[^:]:", label) == 1 && is_label(label)) {
            fprintf(out, "%s:\n", label);
            continue;
        }

        /* ── goto L0 ── */
        char dest[64];
        if(sscanf(line, "goto %63s", dest) == 1) {
            fprintf(out, "    jmp %s\n", dest);
            continue;
        }

        /* ── if N goto L0 ── */
        char cond[64], target[64];
        if(sscanf(line, "if %63s goto %63s", cond, target) == 2) {
            if(strcmp(cond, "NOT") == 0) {
                /* if NOT N goto L0 — skip, handled below */
            } else {
                load_eax(out, cond);
                fprintf(out, "    cmp eax, 0\n");
                fprintf(out, "    jne %s\n", target);
                continue;
            }
        }

        /* ── if NOT N goto L0 ── */
        char not_cond[64], not_target[64];
        if(sscanf(line, "if NOT %63s goto %63s", not_cond, not_target) == 2) {
            load_eax(out, not_cond);
            fprintf(out, "    cmp eax, 0\n");
            fprintf(out, "    je %s\n", not_target);
            continue;
        }

        /* ── print N ── */
        char print_val[64];
        char str_val[256];
        if(sscanf(line, "print_str %[^\n]", str_val) == 1) {
            fprintf(out, "    ; print_str %s\n", str_val);
            int id = -1;
            for(int k=0; k<str_count; k++) {
                if(strcmp(str_literals[k], str_val) == 0) { id = k; break; }
            }
            if(id != -1) {
                fprintf(out, "    lea rcx, [rel str%d]\n", id);
                fprintf(out, "    call printf\n");
            }
            continue;
        }
        else if(sscanf(line, "print %63s", print_val) == 1) {
            fprintf(out, "    ; print %s\n", print_val);
            load_eax(out, print_val);
            fprintf(out, "    lea rcx, [rel fmt]\n");
            fprintf(out, "    mov edx, eax\n");
            fprintf(out, "    call printf\n");
            continue;
        }

        /* ── result = a op b ── */
        char result[64], a[64], op[8], b[64];
        if(sscanf(line, "%63s = %63s %7s %63s", result, a, op, b) == 4) {
            /* strip folded comments from b */
            char clean_b[64];
            sscanf(b, "%63s", clean_b);

            fprintf(out, "    ; %s = %s %s %s\n", result, a, op, clean_b);
            load_eax(out, a);

            if(strcmp(op, "+") == 0) {
                if(is_number(clean_b))
                    fprintf(out, "    add eax, %s\n", clean_b);
                else
                    fprintf(out, "    add eax, [rel %s]\n", clean_b);
            }
            else if(strcmp(op, "-") == 0) {
                if(is_number(clean_b))
                    fprintf(out, "    sub eax, %s\n", clean_b);
                else
                    fprintf(out, "    sub eax, [rel %s]\n", clean_b);
            }
            else if(strcmp(op, "*") == 0) {
                if(is_number(clean_b)) {
                    fprintf(out, "    mov ebx, %s\n", clean_b);
                } else {
                    fprintf(out, "    mov ebx, [rel %s]\n", clean_b);
                }
                fprintf(out, "    imul eax, ebx\n");
            }
            else if(strcmp(op, "/") == 0) {
                if(is_number(clean_b)) {
                    fprintf(out, "    mov ebx, %s\n", clean_b);
                } else {
                    fprintf(out, "    mov ebx, [rel %s]\n", clean_b);
                }
                fprintf(out, "    cdq\n");
                fprintf(out, "    idiv ebx\n");
            }
            else if(strcmp(op, "^") == 0) {
                /* power — use repeated multiplication loop */
                fprintf(out, "    ; power %s ^ %s\n", a, clean_b);
                if(is_number(clean_b)) {
                    fprintf(out, "    mov ecx, %s\n", clean_b);
                } else {
                    fprintf(out, "    mov ecx, [rel %s]\n", clean_b);
                }
                fprintf(out, "    mov edx, eax\n");
                fprintf(out, "    mov eax, 1\n");
                fprintf(out, "pow_loop_%d:\n", i);
                fprintf(out, "    imul eax, edx\n");
                fprintf(out, "    loop pow_loop_%d\n", i);
            }

            fprintf(out, "    mov [rel %s], eax\n", result);
            continue;
        }

        /* ── result = a  (simple assignment) ── */
        char res2[64], val2[64];
        if(sscanf(line, "%63s = %63s", res2, val2) == 2) {
            if(res2[0] == '/' || res2[0] == '=') continue;
            fprintf(out, "    ; %s = %s\n", res2, val2);
            load_eax(out, val2);
            fprintf(out, "    mov [rel %s], eax\n", res2);
            continue;
        }

        /* ── else branch / body / other comments ── */
        fprintf(out, "    ; %s\n", line);
    }
}

/* ── Main ── */
int main() {
    FILE *in  = fopen("phase5_optimized.txt", "r");
    FILE *out = fopen("phase6_assembly.asm",  "w");

    if(!in) {
        printf("ERROR: phase5_optimized.txt not found. Run compiler and optimizer first.\n");
        return 1;
    }
    if(!out) {
        printf("ERROR: Cannot create phase6_assembly.asm\n");
        return 1;
    }

    /* Read all lines */
    char lines[MAX_LINES][MAX_LEN];
    int  line_count = 0;

    while(fgets(lines[line_count], MAX_LEN, in) && line_count < MAX_LINES) {
        lines[line_count][strcspn(lines[line_count], "\r\n")] = 0;
        line_count++;
    }
    fclose(in);

    /* Pass 1 — collect all variable/temp names for .data section */
    collect_vars(lines, line_count);

    /* ── Write ASM file ── */

    /* File header */
    fprintf(out, "; ============================================\n");
    fprintf(out, "; Phase 6 — Generated Assembly (x86 NASM)\n");
    fprintf(out, "; CustomLang Compiler\n");
    fprintf(out, "; Source: phase5_optimized.txt\n");
    fprintf(out, "; ============================================\n\n");

    /* .data section — declare all variables as 32-bit integers */
    fprintf(out, "section .data\n");
    fprintf(out, "    fmt db \"%%d\", 10, 0   ; printf format string\n");
    for(int i = 0; i < str_count; i++) {
        fprintf(out, "    str%d db %s, 10, 0\n", i, str_literals[i]);
    }
    for(int i = 0; i < var_count; i++) {
        /* skip labels and numbers */
        if(is_label(var_names[i])) continue;
        if(is_number(var_names[i])) continue;
        fprintf(out, "    %-15s dd 0\n", var_names[i]);
    }

    /* .bss section for runtime temps if needed */
    fprintf(out, "\nsection .bss\n");
    fprintf(out, "    ; (reserved for future use)\n");

    /* .text section */
    fprintf(out, "\nsection .text\n");
    fprintf(out, "    global main\n");
    fprintf(out, "    extern printf\n\n");
    fprintf(out, "main:\n");
    fprintf(out, "    ; ── function prologue ──\n");
    fprintf(out, "    push rbp\n");
    fprintf(out, "    mov  rbp, rsp\n");
    fprintf(out, "    sub  rsp, 32\n\n");

    /* Pass 2 — generate instructions */
    generate_asm(lines, line_count, out);

    /* function epilogue + exit */
    fprintf(out, "\n    ; ── function epilogue ──\n");
    fprintf(out, "    add  rsp, 32\n");
    fprintf(out, "    pop  rbp\n");
    fprintf(out, "    mov  eax, 0\n");
    fprintf(out, "    ret\n");

    fclose(out);

    printf("Phase 6 complete. See phase6_assembly.asm\n");
    printf("  Variables declared: %d\n", var_count);
    printf("  Lines processed:    %d\n", line_count);
    printf("\nTo assemble and run (requires NASM + GCC):\n");
    printf("  nasm -f win64 phase6_assembly.asm -o phase6.obj\n");
    printf("  gcc phase6.obj -o phase6.exe\n");
    printf("  phase6.exe\n");

    return 0;
}
