@echo off
gcc *.c -o programa_c.exe
if %errorlevel% equ 0 (
    start cmd /k programa_c.exe
)