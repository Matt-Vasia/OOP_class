@echo off
cd /d %~dp0
mkdir build
cd build
cmake ..
cmake --build .
cd Debug
cls
program.exe