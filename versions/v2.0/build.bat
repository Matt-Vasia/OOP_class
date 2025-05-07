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