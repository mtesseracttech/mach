# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.14

# Default target executed when no arguments are given to make.
default_target: all

.PHONY : default_target

# Allow only one "make -f Makefile2" at a time, but pass parallelism.
.NOTPARALLEL:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /opt/JetBrains/apps/CLion/ch-0/191.7479.33/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /opt/JetBrains/apps/CLion/ch-0/191.7479.33/bin/cmake/linux/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/mtesseract/dev/cpp/mach

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/mtesseract/dev/cpp/mach

#=============================================================================
# Targets provided globally by CMake.

# Special rule for the target rebuild_cache
rebuild_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake to regenerate build system..."
	/opt/JetBrains/apps/CLion/ch-0/191.7479.33/bin/cmake/linux/bin/cmake -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : rebuild_cache

# Special rule for the target rebuild_cache
rebuild_cache/fast: rebuild_cache

.PHONY : rebuild_cache/fast

# Special rule for the target edit_cache
edit_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "No interactive CMake dialog available..."
	/opt/JetBrains/apps/CLion/ch-0/191.7479.33/bin/cmake/linux/bin/cmake -E echo No\ interactive\ CMake\ dialog\ available.
.PHONY : edit_cache

# Special rule for the target edit_cache
edit_cache/fast: edit_cache

.PHONY : edit_cache/fast

# The main all target
all: cmake_check_build_system
	$(CMAKE_COMMAND) -E cmake_progress_start /home/mtesseract/dev/cpp/mach/CMakeFiles /home/mtesseract/dev/cpp/mach/CMakeFiles/progress.marks
	$(MAKE) -f CMakeFiles/Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start /home/mtesseract/dev/cpp/mach/CMakeFiles 0
.PHONY : all

# The main clean target
clean:
	$(MAKE) -f CMakeFiles/Makefile2 clean
.PHONY : clean

# The main clean target
clean/fast: clean

.PHONY : clean/fast

# Prepare targets for installation.
preinstall: all
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall

# Prepare targets for installation.
preinstall/fast:
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall/fast

# clear depends
depend:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 1
.PHONY : depend

#=============================================================================
# Target rules for targets named mach

# Build rule for target.
mach: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 mach
.PHONY : mach

# fast build rule for target.
mach/fast:
	$(MAKE) -f CMakeFiles/mach.dir/build.make CMakeFiles/mach.dir/build
.PHONY : mach/fast

lib/glad.o: lib/glad.c.o

.PHONY : lib/glad.o

# target to build an object file
lib/glad.c.o:
	$(MAKE) -f CMakeFiles/mach.dir/build.make CMakeFiles/mach.dir/lib/glad.c.o
.PHONY : lib/glad.c.o

lib/glad.i: lib/glad.c.i

.PHONY : lib/glad.i

# target to preprocess a source file
lib/glad.c.i:
	$(MAKE) -f CMakeFiles/mach.dir/build.make CMakeFiles/mach.dir/lib/glad.c.i
.PHONY : lib/glad.c.i

lib/glad.s: lib/glad.c.s

.PHONY : lib/glad.s

# target to generate assembly for a file
lib/glad.c.s:
	$(MAKE) -f CMakeFiles/mach.dir/build.make CMakeFiles/mach.dir/lib/glad.c.s
.PHONY : lib/glad.c.s

src/MachApplication.o: src/MachApplication.cpp.o

.PHONY : src/MachApplication.o

# target to build an object file
src/MachApplication.cpp.o:
	$(MAKE) -f CMakeFiles/mach.dir/build.make CMakeFiles/mach.dir/src/MachApplication.cpp.o
.PHONY : src/MachApplication.cpp.o

src/MachApplication.i: src/MachApplication.cpp.i

.PHONY : src/MachApplication.i

# target to preprocess a source file
src/MachApplication.cpp.i:
	$(MAKE) -f CMakeFiles/mach.dir/build.make CMakeFiles/mach.dir/src/MachApplication.cpp.i
.PHONY : src/MachApplication.cpp.i

src/MachApplication.s: src/MachApplication.cpp.s

.PHONY : src/MachApplication.s

# target to generate assembly for a file
src/MachApplication.cpp.s:
	$(MAKE) -f CMakeFiles/mach.dir/build.make CMakeFiles/mach.dir/src/MachApplication.cpp.s
.PHONY : src/MachApplication.cpp.s

src/auxiliary/logging/Logger.o: src/auxiliary/logging/Logger.cpp.o

.PHONY : src/auxiliary/logging/Logger.o

# target to build an object file
src/auxiliary/logging/Logger.cpp.o:
	$(MAKE) -f CMakeFiles/mach.dir/build.make CMakeFiles/mach.dir/src/auxiliary/logging/Logger.cpp.o
.PHONY : src/auxiliary/logging/Logger.cpp.o

src/auxiliary/logging/Logger.i: src/auxiliary/logging/Logger.cpp.i

.PHONY : src/auxiliary/logging/Logger.i

# target to preprocess a source file
src/auxiliary/logging/Logger.cpp.i:
	$(MAKE) -f CMakeFiles/mach.dir/build.make CMakeFiles/mach.dir/src/auxiliary/logging/Logger.cpp.i
.PHONY : src/auxiliary/logging/Logger.cpp.i

src/auxiliary/logging/Logger.s: src/auxiliary/logging/Logger.cpp.s

.PHONY : src/auxiliary/logging/Logger.s

# target to generate assembly for a file
src/auxiliary/logging/Logger.cpp.s:
	$(MAKE) -f CMakeFiles/mach.dir/build.make CMakeFiles/mach.dir/src/auxiliary/logging/Logger.cpp.s
.PHONY : src/auxiliary/logging/Logger.cpp.s

src/auxiliary/time/Timer.o: src/auxiliary/time/Timer.cpp.o

.PHONY : src/auxiliary/time/Timer.o

# target to build an object file
src/auxiliary/time/Timer.cpp.o:
	$(MAKE) -f CMakeFiles/mach.dir/build.make CMakeFiles/mach.dir/src/auxiliary/time/Timer.cpp.o
.PHONY : src/auxiliary/time/Timer.cpp.o

src/auxiliary/time/Timer.i: src/auxiliary/time/Timer.cpp.i

.PHONY : src/auxiliary/time/Timer.i

# target to preprocess a source file
src/auxiliary/time/Timer.cpp.i:
	$(MAKE) -f CMakeFiles/mach.dir/build.make CMakeFiles/mach.dir/src/auxiliary/time/Timer.cpp.i
.PHONY : src/auxiliary/time/Timer.cpp.i

src/auxiliary/time/Timer.s: src/auxiliary/time/Timer.cpp.s

.PHONY : src/auxiliary/time/Timer.s

# target to generate assembly for a file
src/auxiliary/time/Timer.cpp.s:
	$(MAKE) -f CMakeFiles/mach.dir/build.make CMakeFiles/mach.dir/src/auxiliary/time/Timer.cpp.s
.PHONY : src/auxiliary/time/Timer.cpp.s

src/graphics/renderer/OpenGLRenderer.o: src/graphics/renderer/OpenGLRenderer.cpp.o

.PHONY : src/graphics/renderer/OpenGLRenderer.o

# target to build an object file
src/graphics/renderer/OpenGLRenderer.cpp.o:
	$(MAKE) -f CMakeFiles/mach.dir/build.make CMakeFiles/mach.dir/src/graphics/renderer/OpenGLRenderer.cpp.o
.PHONY : src/graphics/renderer/OpenGLRenderer.cpp.o

src/graphics/renderer/OpenGLRenderer.i: src/graphics/renderer/OpenGLRenderer.cpp.i

.PHONY : src/graphics/renderer/OpenGLRenderer.i

# target to preprocess a source file
src/graphics/renderer/OpenGLRenderer.cpp.i:
	$(MAKE) -f CMakeFiles/mach.dir/build.make CMakeFiles/mach.dir/src/graphics/renderer/OpenGLRenderer.cpp.i
.PHONY : src/graphics/renderer/OpenGLRenderer.cpp.i

src/graphics/renderer/OpenGLRenderer.s: src/graphics/renderer/OpenGLRenderer.cpp.s

.PHONY : src/graphics/renderer/OpenGLRenderer.s

# target to generate assembly for a file
src/graphics/renderer/OpenGLRenderer.cpp.s:
	$(MAKE) -f CMakeFiles/mach.dir/build.make CMakeFiles/mach.dir/src/graphics/renderer/OpenGLRenderer.cpp.s
.PHONY : src/graphics/renderer/OpenGLRenderer.cpp.s

src/graphics/renderer/Renderer.o: src/graphics/renderer/Renderer.cpp.o

.PHONY : src/graphics/renderer/Renderer.o

# target to build an object file
src/graphics/renderer/Renderer.cpp.o:
	$(MAKE) -f CMakeFiles/mach.dir/build.make CMakeFiles/mach.dir/src/graphics/renderer/Renderer.cpp.o
.PHONY : src/graphics/renderer/Renderer.cpp.o

src/graphics/renderer/Renderer.i: src/graphics/renderer/Renderer.cpp.i

.PHONY : src/graphics/renderer/Renderer.i

# target to preprocess a source file
src/graphics/renderer/Renderer.cpp.i:
	$(MAKE) -f CMakeFiles/mach.dir/build.make CMakeFiles/mach.dir/src/graphics/renderer/Renderer.cpp.i
.PHONY : src/graphics/renderer/Renderer.cpp.i

src/graphics/renderer/Renderer.s: src/graphics/renderer/Renderer.cpp.s

.PHONY : src/graphics/renderer/Renderer.s

# target to generate assembly for a file
src/graphics/renderer/Renderer.cpp.s:
	$(MAKE) -f CMakeFiles/mach.dir/build.make CMakeFiles/mach.dir/src/graphics/renderer/Renderer.cpp.s
.PHONY : src/graphics/renderer/Renderer.cpp.s

src/graphics/shaders/OpenGLShader.o: src/graphics/shaders/OpenGLShader.cpp.o

.PHONY : src/graphics/shaders/OpenGLShader.o

# target to build an object file
src/graphics/shaders/OpenGLShader.cpp.o:
	$(MAKE) -f CMakeFiles/mach.dir/build.make CMakeFiles/mach.dir/src/graphics/shaders/OpenGLShader.cpp.o
.PHONY : src/graphics/shaders/OpenGLShader.cpp.o

src/graphics/shaders/OpenGLShader.i: src/graphics/shaders/OpenGLShader.cpp.i

.PHONY : src/graphics/shaders/OpenGLShader.i

# target to preprocess a source file
src/graphics/shaders/OpenGLShader.cpp.i:
	$(MAKE) -f CMakeFiles/mach.dir/build.make CMakeFiles/mach.dir/src/graphics/shaders/OpenGLShader.cpp.i
.PHONY : src/graphics/shaders/OpenGLShader.cpp.i

src/graphics/shaders/OpenGLShader.s: src/graphics/shaders/OpenGLShader.cpp.s

.PHONY : src/graphics/shaders/OpenGLShader.s

# target to generate assembly for a file
src/graphics/shaders/OpenGLShader.cpp.s:
	$(MAKE) -f CMakeFiles/mach.dir/build.make CMakeFiles/mach.dir/src/graphics/shaders/OpenGLShader.cpp.s
.PHONY : src/graphics/shaders/OpenGLShader.cpp.s

src/graphics/window/OpenGLWindow.o: src/graphics/window/OpenGLWindow.cpp.o

.PHONY : src/graphics/window/OpenGLWindow.o

# target to build an object file
src/graphics/window/OpenGLWindow.cpp.o:
	$(MAKE) -f CMakeFiles/mach.dir/build.make CMakeFiles/mach.dir/src/graphics/window/OpenGLWindow.cpp.o
.PHONY : src/graphics/window/OpenGLWindow.cpp.o

src/graphics/window/OpenGLWindow.i: src/graphics/window/OpenGLWindow.cpp.i

.PHONY : src/graphics/window/OpenGLWindow.i

# target to preprocess a source file
src/graphics/window/OpenGLWindow.cpp.i:
	$(MAKE) -f CMakeFiles/mach.dir/build.make CMakeFiles/mach.dir/src/graphics/window/OpenGLWindow.cpp.i
.PHONY : src/graphics/window/OpenGLWindow.cpp.i

src/graphics/window/OpenGLWindow.s: src/graphics/window/OpenGLWindow.cpp.s

.PHONY : src/graphics/window/OpenGLWindow.s

# target to generate assembly for a file
src/graphics/window/OpenGLWindow.cpp.s:
	$(MAKE) -f CMakeFiles/mach.dir/build.make CMakeFiles/mach.dir/src/graphics/window/OpenGLWindow.cpp.s
.PHONY : src/graphics/window/OpenGLWindow.cpp.s

src/graphics/window/RenderWindow.o: src/graphics/window/RenderWindow.cpp.o

.PHONY : src/graphics/window/RenderWindow.o

# target to build an object file
src/graphics/window/RenderWindow.cpp.o:
	$(MAKE) -f CMakeFiles/mach.dir/build.make CMakeFiles/mach.dir/src/graphics/window/RenderWindow.cpp.o
.PHONY : src/graphics/window/RenderWindow.cpp.o

src/graphics/window/RenderWindow.i: src/graphics/window/RenderWindow.cpp.i

.PHONY : src/graphics/window/RenderWindow.i

# target to preprocess a source file
src/graphics/window/RenderWindow.cpp.i:
	$(MAKE) -f CMakeFiles/mach.dir/build.make CMakeFiles/mach.dir/src/graphics/window/RenderWindow.cpp.i
.PHONY : src/graphics/window/RenderWindow.cpp.i

src/graphics/window/RenderWindow.s: src/graphics/window/RenderWindow.cpp.s

.PHONY : src/graphics/window/RenderWindow.s

# target to generate assembly for a file
src/graphics/window/RenderWindow.cpp.s:
	$(MAKE) -f CMakeFiles/mach.dir/build.make CMakeFiles/mach.dir/src/graphics/window/RenderWindow.cpp.s
.PHONY : src/graphics/window/RenderWindow.cpp.s

src/io/input/KeyInput.o: src/io/input/KeyInput.cpp.o

.PHONY : src/io/input/KeyInput.o

# target to build an object file
src/io/input/KeyInput.cpp.o:
	$(MAKE) -f CMakeFiles/mach.dir/build.make CMakeFiles/mach.dir/src/io/input/KeyInput.cpp.o
.PHONY : src/io/input/KeyInput.cpp.o

src/io/input/KeyInput.i: src/io/input/KeyInput.cpp.i

.PHONY : src/io/input/KeyInput.i

# target to preprocess a source file
src/io/input/KeyInput.cpp.i:
	$(MAKE) -f CMakeFiles/mach.dir/build.make CMakeFiles/mach.dir/src/io/input/KeyInput.cpp.i
.PHONY : src/io/input/KeyInput.cpp.i

src/io/input/KeyInput.s: src/io/input/KeyInput.cpp.s

.PHONY : src/io/input/KeyInput.s

# target to generate assembly for a file
src/io/input/KeyInput.cpp.s:
	$(MAKE) -f CMakeFiles/mach.dir/build.make CMakeFiles/mach.dir/src/io/input/KeyInput.cpp.s
.PHONY : src/io/input/KeyInput.cpp.s

src/io/input/MouseInput.o: src/io/input/MouseInput.cpp.o

.PHONY : src/io/input/MouseInput.o

# target to build an object file
src/io/input/MouseInput.cpp.o:
	$(MAKE) -f CMakeFiles/mach.dir/build.make CMakeFiles/mach.dir/src/io/input/MouseInput.cpp.o
.PHONY : src/io/input/MouseInput.cpp.o

src/io/input/MouseInput.i: src/io/input/MouseInput.cpp.i

.PHONY : src/io/input/MouseInput.i

# target to preprocess a source file
src/io/input/MouseInput.cpp.i:
	$(MAKE) -f CMakeFiles/mach.dir/build.make CMakeFiles/mach.dir/src/io/input/MouseInput.cpp.i
.PHONY : src/io/input/MouseInput.cpp.i

src/io/input/MouseInput.s: src/io/input/MouseInput.cpp.s

.PHONY : src/io/input/MouseInput.s

# target to generate assembly for a file
src/io/input/MouseInput.cpp.s:
	$(MAKE) -f CMakeFiles/mach.dir/build.make CMakeFiles/mach.dir/src/io/input/MouseInput.cpp.s
.PHONY : src/io/input/MouseInput.cpp.s

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... rebuild_cache"
	@echo "... mach"
	@echo "... edit_cache"
	@echo "... lib/glad.o"
	@echo "... lib/glad.i"
	@echo "... lib/glad.s"
	@echo "... src/MachApplication.o"
	@echo "... src/MachApplication.i"
	@echo "... src/MachApplication.s"
	@echo "... src/auxiliary/logging/Logger.o"
	@echo "... src/auxiliary/logging/Logger.i"
	@echo "... src/auxiliary/logging/Logger.s"
	@echo "... src/auxiliary/time/Timer.o"
	@echo "... src/auxiliary/time/Timer.i"
	@echo "... src/auxiliary/time/Timer.s"
	@echo "... src/graphics/renderer/OpenGLRenderer.o"
	@echo "... src/graphics/renderer/OpenGLRenderer.i"
	@echo "... src/graphics/renderer/OpenGLRenderer.s"
	@echo "... src/graphics/renderer/Renderer.o"
	@echo "... src/graphics/renderer/Renderer.i"
	@echo "... src/graphics/renderer/Renderer.s"
	@echo "... src/graphics/shaders/OpenGLShader.o"
	@echo "... src/graphics/shaders/OpenGLShader.i"
	@echo "... src/graphics/shaders/OpenGLShader.s"
	@echo "... src/graphics/window/OpenGLWindow.o"
	@echo "... src/graphics/window/OpenGLWindow.i"
	@echo "... src/graphics/window/OpenGLWindow.s"
	@echo "... src/graphics/window/RenderWindow.o"
	@echo "... src/graphics/window/RenderWindow.i"
	@echo "... src/graphics/window/RenderWindow.s"
	@echo "... src/io/input/KeyInput.o"
	@echo "... src/io/input/KeyInput.i"
	@echo "... src/io/input/KeyInput.s"
	@echo "... src/io/input/MouseInput.o"
	@echo "... src/io/input/MouseInput.i"
	@echo "... src/io/input/MouseInput.s"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system
