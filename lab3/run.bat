@echo off
"C:\Program Files\Microsoft Visual Studio\2022\Community\Common7\IDE\CommonExtensions\Microsoft\CMake\CMake\bin\cmake.exe" --build c:/Users/17D3~1/PP/build --config Debug --target ALL_BUILD -j 16 --
cd build\Debug
mpiexec -n 8 ./lab3.exe
cd /d C:\Users\17D3~1\PP