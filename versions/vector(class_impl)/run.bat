@echo off
cd /d %~dp0
echo Creating build directory...
if not exist build mkdir build
cd build

echo Running CMake configuration...
cmake ..
if %ERRORLEVEL% NEQ 0 (
    echo CMake configuration failed! Make sure CMake is installed and in your PATH.
    pause
    exit /b 1
)

echo Building project...
cmake --build . --config Release
if %ERRORLEVEL% NEQ 0 (
    echo Build failed!
    pause
    exit /b 1
)

echo Looking for program executable...
if exist Release\program.exe (
    cd Release
) else if exist program.exe (
    rem Already in the right directory
) else (
    echo Program executable not found!
    pause
    exit /b 1
)

cls
echo Running program...
program.exe

pause