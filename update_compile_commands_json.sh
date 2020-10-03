#!/bin/bash
rm -rf build/ bin/
mkdir -p build/
cmake -B build -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
cp ./build/compile_commands.json .
rm -rf build/ bin/
cmake -B build
