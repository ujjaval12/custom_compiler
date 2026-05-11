@echo off
echo ============================================
echo  Phase 7 — Linker and Loader
echo  Assembles and links phase6_assembly.asm
echo  into a real executable: final.exe
echo ============================================
echo.

REM ── Step 1: Check NASM is available ──
where nasm >nul 2>&1
if errorlevel 1 (
    echo ERROR: NASM not found.
    echo Download from https://www.nasm.us/pub/nasm/releasebuilds/
    echo Install it and add to PATH then run this again.
    pause
    exit
)
echo NASM found OK.

REM ── Step 2: Check input file exists ──
if not exist phase6_assembly.asm (
    echo ERROR: phase6_assembly.asm not found.
    echo Run build.bat first to generate it.
    pause
    exit
)
echo phase6_assembly.asm found OK.

REM ── Step 3: Assemble with NASM ──
echo.
echo [Step 1] Assembling with NASM...
nasm -f win64 phase6_assembly.asm -o phase7_object.obj 2> phase7_nasm_errors.txt
if errorlevel 1 (
    echo NASM FAILED. See phase7_nasm_errors.txt for details.
    type phase7_nasm_errors.txt
    pause
    exit
)
echo NASM OK — phase7_object.obj generated

REM ── Step 4: Link with GCC ──
echo.
echo [Step 2] Linking with GCC...
gcc phase7_object.obj -o final.exe 2> phase7_link_errors.txt
if errorlevel 1 (
    echo LINKING FAILED. See phase7_link_errors.txt for details.
    type phase7_link_errors.txt
    pause
    exit
)
echo GCC Linker OK — final.exe generated

REM ── Step 5: Run the final executable ──
echo.
echo [Step 3] Running final.exe...
echo ----------------------------------------
final.exe > phase7_final_output.txt 2>&1
type phase7_final_output.txt
echo ----------------------------------------
echo.

echo ============================================
echo  Phase 7 Complete
echo ============================================
echo  phase7_object.obj      — compiled object file
echo  final.exe              — final executable
echo  phase7_final_output.txt— program output
echo ============================================
pause
