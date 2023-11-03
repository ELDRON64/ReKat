echo off

cmake . -B Build 

cd Build

make 

cd ReKat

echo "ended compilation (msg from compile)";
echo "running (msg from compile)";

./ReKat $1
