@echo off
setlocal

mkdir build
cd build
cmake ..
cmake --build .
pause