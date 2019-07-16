
Conan setup:

Linux:
filename: ~/.conan/profiles/clang

******************************
[settings]
compiler=clang
compiler.version=8
compiler.libcxx=libstdc++11
arch=x86_64
os=Linux

[env]
CC=/usr/bin/clang
CXX=/usr/bin/clang++
******************************

build arguments:
cd to project root (folder this file is in)

mkdir .conan && cd .conan
conan install .. --profile clang --build=missing

