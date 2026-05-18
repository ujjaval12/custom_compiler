@echo off
echo ============================================
echo  Running all phases on input.txt
echo ============================================

echo.
echo [Phase 1,2,3,4] Running compiler...
compiler.exe < input.txt
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
