/*
 * Phase 5 — Code Optimizer
 * Reads phase4_tac.txt, applies optimizations, writes phase5_optimized.txt
 *
 * Optimizations implemented:
 *   1. Constant Folding   — t0 = 2 + 3  becomes  t0 = 5
 *   2. Constant Propagation — if x=5 then t1=x+2 becomes t1=7
 *   3. Dead Code Elimination — temps never used again are removed
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LINES   1000
#define MAX_LEN     256
#define MAX_VARS    200

/* ── Symbol table for constant propagation ── */
typedef struct {
    char name[64];
    int  value;
    int  is_const;   /* 1 = known constant, 0 = unknown */
} ConstEntry;

ConstEntry const_table[MAX_VARS];
int const_count = 0;

/* ── TAC line store ── */
char lines[MAX_LINES][MAX_LEN];
int  used[MAX_LINES];   /* 0 = dead, 1 = alive */
int  line_count = 0;

/* ── Stats ── */
int folded   = 0;
int propagated = 0;
int eliminated = 0;

/* ─────────────────────────────────────── */
/* Constant table helpers                  */
/* ─────────────────────────────────────── */

int get_const(const char *name, int *out_val) {
    for(int i = 0; i < const_count; i++) {
        if(strcmp(const_table[i].name, name) == 0 && const_table[i].is_const) {
            *out_val = const_table[i].value;
            return 1;
        }
    }
    return 0;
}

void set_const(const char *name, int value) {
    for(int i = 0; i < const_count; i++) {
        if(strcmp(const_table[i].name, name) == 0) {
            const_table[i].value    = value;
            const_table[i].is_const = 1;
            return;
        }
    }
    strcpy(const_table[const_count].name,  name);
    const_table[const_count].value    = value;
    const_table[const_count].is_const = 1;
    const_count++;
}

void invalidate_const(const char *name) {
    for(int i = 0; i < const_count; i++) {
        if(strcmp(const_table[i].name, name) == 0) {
            const_table[i].is_const = 0;
            return;
        }
    }
}

/* ─────────────────────────────────────── */
/* Helper: is string a plain integer?      */
/* ─────────────────────────────────────── */
int is_number(const char *s) {
    if(!s || !*s) return 0;
    int i = 0;
    if(s[0] == '-') i = 1;
    for(; s[i]; i++)
        if(!isdigit((unsigned char)s[i])) return 0;
    return 1;
}

/* ─────────────────────────────────────── */
/* Optimization 1 — Constant Folding       */
/* t0 = 5 + 3   →   t0 = 8               */
/* ─────────────────────────────────────── */
int try_constant_fold(char *line, char *out) {
    char result[64], a[64], op[8], b[64];
    if(sscanf(line, "%s = %s %s %s", result, a, op, b) != 4) return 0;

    /* resolve a and b — try constant propagation too */
    int va, vb;
    int a_known = is_number(a) ? (va = atoi(a), 1) : get_const(a, &va);
    int b_known = is_number(b) ? (vb = atoi(b), 1) : get_const(b, &vb);

    if(!a_known || !b_known) return 0;

    int res = 0;
    if     (strcmp(op, "+") == 0) res = va + vb;
    else if(strcmp(op, "-") == 0) res = va - vb;
    else if(strcmp(op, "*") == 0) res = va * vb;
    else if(strcmp(op, "/") == 0) {
        if(vb == 0) { sprintf(out, "%s = 0  /* div by zero */", result); return 1; }
        res = va / vb;
    }
    else if(strcmp(op, "^") == 0) {
        res = 1;
        for(int i = 0; i < vb; i++) res *= va;
    }
    else return 0;

    sprintf(out, "%s = %d  /* folded: %d %s %d */", result, res, va, op, vb);
    set_const(result, res);
    folded++;
    return 1;
}

/* ─────────────────────────────────────── */
/* Optimization 2 — Constant Propagation   */
/* x = 5; t1 = x + 2  →  t1 = 5 + 2     */
/* (then folding kicks in)                 */
/* ─────────────────────────────────────── */
void try_propagate(char *line, char *out) {
    char result[64], a[64], op[8], b[64];
    strcpy(out, line);

    /* simple assignment: x = 5 */
    if(sscanf(line, "%s = %s", result, a) == 2 && !strchr(a, '=')) {
        if(is_number(a)) {
            set_const(result, atoi(a));
        } else {
            int v;
            if(get_const(a, &v)) {
                sprintf(out, "%s = %d  /* propagated from %s */", result, v, a);
                set_const(result, v);
                propagated++;
            } else {
                invalidate_const(result);
            }
        }
        return;
    }

    /* binary: result = a op b */
    if(sscanf(line, "%s = %s %s %s", result, a, op, b) == 4) {
        int changed = 0;
        int va, vb;
        char new_a[64], new_b[64];
        strcpy(new_a, a);
        strcpy(new_b, b);

        if(!is_number(a) && get_const(a, &va)) {
            sprintf(new_a, "%d", va);
            changed = 1;
        }
        if(!is_number(b) && get_const(b, &vb)) {
            sprintf(new_b, "%d", vb);
            changed = 1;
        }
        if(changed) {
            sprintf(out, "%s = %s %s %s  /* propagated */", result, new_a, op, new_b);
            propagated++;
        }
        invalidate_const(result);
    }
}

/* ─────────────────────────────────────── */
/* Optimization 3 — Dead Code Elimination  */
/* Mark temp vars that are never read      */
/* ─────────────────────────────────────── */
void dead_code_elimination() {
    /* For each line that assigns a temp (t0, t1 ...) */
    /* check if that temp appears on the RHS of any later line */
    for(int i = 0; i < line_count; i++) {
        char result[64], rest[MAX_LEN];
        if(sscanf(lines[i], "%s = %[^\n]", result, rest) != 2) continue;
        /* only eliminate temps, not user variables */
        if(result[0] != 't' || !isdigit((unsigned char)result[1])) continue;

        int used_later = 0;
        for(int j = i + 1; j < line_count; j++) {
            if(strstr(lines[j], result)) { used_later = 1; break; }
        }
        if(!used_later) {
            used[i] = 0;
            eliminated++;
        }
    }
}

/* ─────────────────────────────────────── */
/* Main optimizer logic                    */
/* ─────────────────────────────────────── */
int main() {
    FILE *in  = fopen("phase4_tac.txt",      "r");
    FILE *out = fopen("phase5_optimized.txt", "w");

    if(!in) {
        printf("ERROR: phase4_tac.txt not found. Run compiler first.\n");
        return 1;
    }
    if(!out) {
        printf("ERROR: Cannot create phase5_optimized.txt\n");
        return 1;
    }

    /* Read all TAC lines */
    while(fgets(lines[line_count], MAX_LEN, in) && line_count < MAX_LINES) {
        /* strip trailing newline */
        lines[line_count][strcspn(lines[line_count], "\r\n")] = 0;
        used[line_count] = 1;
        line_count++;
    }
    fclose(in);

    fprintf(out, "=== PHASE 5: OPTIMIZED THREE ADDRESS CODE ===\n\n");
    fprintf(out, "Input:  phase4_tac.txt\n");
    fprintf(out, "Output: phase5_optimized.txt\n\n");
    fprintf(out, "Optimizations applied:\n");
    fprintf(out, "  1. Constant Folding\n");
    fprintf(out, "  2. Constant Propagation\n");
    fprintf(out, "  3. Dead Code Elimination\n\n");
    fprintf(out, "─────────────────────────────────────────\n");
    fprintf(out, "BEFORE OPTIMIZATION:\n");
    fprintf(out, "─────────────────────────────────────────\n");
    for(int i = 0; i < line_count; i++)
        fprintf(out, "%s\n", lines[i]);

    /* Pass 1 — Constant propagation + folding */
    char optimized[MAX_LINES][MAX_LEN];
    for(int i = 0; i < line_count; i++) {
        /* skip header/empty lines */
        if(lines[i][0] == '=' || lines[i][0] == '\0' || lines[i][0] == '-') {
            strcpy(optimized[i], lines[i]);
            continue;
        }

        char after_prop[MAX_LEN];
        try_propagate(lines[i], after_prop);

        char after_fold[MAX_LEN];
        if(try_constant_fold(after_prop, after_fold)) {
            strcpy(optimized[i], after_fold);
        } else {
            strcpy(optimized[i], after_prop);
        }
        strcpy(lines[i], optimized[i]);
    }

    /* Pass 2 — Dead code elimination */
    dead_code_elimination();

    /* Write final output */
    fprintf(out, "\n─────────────────────────────────────────\n");
    fprintf(out, "AFTER OPTIMIZATION:\n");
    fprintf(out, "─────────────────────────────────────────\n");
    for(int i = 0; i < line_count; i++) {
        if(used[i]) fprintf(out, "%s\n", optimized[i]);
        else        fprintf(out, "/* ELIMINATED: %s */\n", optimized[i]);
    }

    fprintf(out, "\n─────────────────────────────────────────\n");
    fprintf(out, "OPTIMIZATION SUMMARY:\n");
    fprintf(out, "─────────────────────────────────────────\n");
    fprintf(out, "  Constants folded:      %d\n", folded);
    fprintf(out, "  Variables propagated:  %d\n", propagated);
    fprintf(out, "  Dead lines eliminated: %d\n", eliminated);
    fprintf(out, "  Total optimizations:   %d\n", folded + propagated + eliminated);

    fclose(out);
    printf("Phase 5 complete. See phase5_optimized.txt\n");
    printf("  Folded:     %d\n", folded);
    printf("  Propagated: %d\n", propagated);
    printf("  Eliminated: %d\n", eliminated);
    return 0;
}
