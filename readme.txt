SETUP

GENERAL:

- Install python 3
- Install pip
- Install conan
pip install conan
- Generate a default profile with:
conan profile new clang --detect
- Adjust as needed
- Follow the relevant platform dependent bit below:



LINUX:

profile contents:
******************************
[settings]
os=Linux
os_build=Linux
arch=x86_64
arch_build=x86_64
compiler=clang
compiler.version=8
compiler.libcxx=libstdc++11
build_type=Release

[options]

[build_requires]

[env]
CC=/usr/bin/clang
CXX=/usr/bin/clang++
******************************

Go to BUILDING at the bottom.



OSX:

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

Go to BUILDING at the bottom.



WINDOWS:

Install msys2 to C:/msys64

pacman -Syu (close and reopen the console if needed)
pacman -Su
pacman -S mingw-w64-x86_64-toolchain
pacman -S mingw-w64-x86_64-clang

Add C:\msys64\mingw64\bin\ to PATH

Clion settings:
Environment: C:\msys64\mingw64
Cmake: Bundled
Make: C:\msys64\mingw64\bin\mingw32-make.exe
C Compiler: C:\msys64\mingw64\bin\clang.exe
C++ Compiler: C:\msys64\mingw64\bin\clang++.exe
Debugger: C:\msys64\mingw64\bin\gdb.exe

Install Cmake separately as needed.

******************************
[settings]
os=Windows
os_build=Windows
arch=x86_64
arch_build=x86_64
compiler=clang
compiler.version=8
compiler.libcxx=libstdc++
build_type=Release
[options]
[build_requires]
[env]
CC=C:\msys64\mingw64\bin\clang.exe
CXX=C:\msys64\mingw64\bin\clang++.exe


******************************


BUILDING:

cd to project root (folder this file is in)
mkdir .conan && cd .conan
conan install .. --profile clang --build=missing
Just wait till the dependencies download and compile.