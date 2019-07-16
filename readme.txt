
Conan setup:

Linux:
profile filename: ~/.conan/profiles/clang
contents:
******************************
[settings]
compiler=clang
compiler.version=8
compiler.libcxx=libstdc++11
arch=x86_64
os=Linux

[options]

[build_requires]

[env]
CC=/usr/bin/clang
CXX=/usr/bin/clang++
******************************


OSX
In case of error relating to not being able to find certain basic files like cmath, reinstall the SDK headers.

sudo installer -pkg /Library/Developer/CommandLineTools/Packages/macOS_SDK_headers_for_macOS_10.14.pkg -target /

profile filename: ~/.conan/profiles/clang
contents:
******************************
[settings]
os=Macos
os_build=Macos
arch=x86_64
arch_build=x86_64
compiler=apple-clang
compiler.version=10.0
compiler.libcxx=libc++
build_type=Release

[options]

[build_requires]

[env]
******************************

building:
cd to project root (folder this file is in)
mkdir .conan && cd .conan
conan install .. --profile clang --build=missing

