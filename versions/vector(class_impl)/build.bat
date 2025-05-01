@echo off
cd /d %~dp0

if not exist build mkdir build
cd build

cmake ..
if %ERRORLEVEL% NEQ 0 (
    echo CMake configuration failed! Make sure CMake is installed and in your PATH.
    pause
    exit /b 1
)

cmake --build . --config Release
if %ERRORLEVEL% NEQ 0 (
    echo Build failed!
    pause
    exit /b 1
)

if exist Release\program.exe (
    cd Release
) else if exist program.exe (
    rem Already in the right directory
) else (
    echo Program executable not found!
    pause
    exit /b 1
)