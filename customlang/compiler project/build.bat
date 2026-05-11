@echo off
echo ============================================
echo  CustomLang Compiler — Full Build Pipeline
echo  All 7 Compiler Phases
echo ============================================
echo.

echo [Phase 1+2+3+4] Running Flex...
win_flex 1807002.l
if errorlevel 1 ( echo FLEX FAILED & pause & exit )
echo Flex OK — lex.yy.c generated

echo.
echo [Phase 1+2+3+4] Running Bison...
win_bison -d 1807002.y -o 1807002.tab.c
if errorlevel 1 ( echo BISON FAILED & pause & exit )
echo Bison OK — 1807002.tab.c and 1807002.tab.h generated

echo.
echo [Phase 1+2+3+4] Compiling compiler with GCC...
gcc lex.yy.c 1807002.tab.c -o compiler.exe -lm
if errorlevel 1 ( echo GCC COMPILE FAILED & pause & exit )
echo GCC OK — compiler.exe ready

echo.
echo [Phase 5] Compiling optimizer...
gcc optimizer.c -o optimizer.exe
if errorlevel 1 ( echo OPTIMIZER COMPILE FAILED & pause & exit )
echo Optimizer OK — optimizer.exe ready

echo.
echo [Phase 6] Compiling code generator...
gcc codegen.c -o codegen.exe
if errorlevel 1 ( echo CODEGEN COMPILE FAILED & pause & exit )
echo CodeGen OK — codegen.exe ready

echo.
echo ============================================
echo  Running all phases on test_input.txt
echo ============================================

echo.
echo [Phase 1,2,3,4] Running compiler...
compiler.exe < test_input.txt
echo Compiler done — phase1/2/3/4 output files generated.

echo.
echo [Phase 5] Running optimizer...
optimizer.exe
echo Optimizer done — phase5_optimized.txt generated.

echo.
echo [Phase 6] Running code generator...
codegen.exe
echo Code generation done — phase6_assembly.asm generated.

echo.
echo [Phase 7] Running linker...
where nasm >nul 2>&1
if errorlevel 1 (
    echo NASM not found — skipping Phase 7.
    echo Run nasm_setup.bat to install NASM then run linker.bat manually.
) else (
    nasm -f win64 phase6_assembly.asm -o phase7_object.obj
    if errorlevel 1 (
        echo NASM assembly failed.
    ) else (
        gcc phase7_object.obj -o final.exe
        if errorlevel 1 (
            echo Linking failed.
        ) else (
            echo Linker OK — final.exe generated.
            final.exe > phase7_final_output.txt 2>&1
            echo final.exe ran — output in phase7_final_output.txt
        )
    )
)

echo.
echo ============================================
echo  ALL OUTPUT FILES — ONE PER PHASE
echo ============================================
echo  output.txt             — full compiler trace
echo  phase1_lexer.txt       — Phase 1: token list
echo  phase2_parser.txt      — Phase 2: grammar rules
echo  phase3_semantic.txt    — Phase 3: symbol table
echo  phase4_tac.txt         — Phase 4: three address code
echo  phase5_optimized.txt   — Phase 5: optimized TAC
echo  phase6_assembly.asm    — Phase 6: x86 assembly
echo  phase7_object.obj      — Phase 7: object file
echo  final.exe              — Phase 7: final executable
echo  phase7_final_output.txt— Phase 7: program output
echo ============================================
pause
