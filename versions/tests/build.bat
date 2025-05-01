@echo off
cd /d %~dp0

if not exist build mkdir build
cd build

cmake ..

cd ..

cmake --build build

cd build
cd Debug

copy tests.exe "../.."

pause