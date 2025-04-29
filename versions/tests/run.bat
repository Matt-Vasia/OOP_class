@echo off
cd /d %~dp0

if not exist build mkdir build
cd build

cmake ..

cmake --build build

if exist Debug\tests.exe (
    cd Debug
) else if exist tests.exe (
    rem Already in the right directory
) else (
    echo Program executable not found!
    pause
    exit /b 1
)

cls
tests.exe

pause