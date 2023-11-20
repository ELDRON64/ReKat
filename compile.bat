echo off

cmake . -B ../Build_m -G "MinGW Makefiles"

cd ../Build_m

mingw32-make

cd ReKat

echo ended compilation (msg from compile)
echo running (msg from compile)

.\ReKat

cd ../../