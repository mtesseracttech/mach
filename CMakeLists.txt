cmake_minimum_required(VERSION 3.14)
project(mach)

set(CMAKE_CXX_STANDARD 17)

# Adding libdl, which is a dependency for GLAD on non-windows platforms and may not be recognized otherwise
set(CMAKE_CXX_LINK_EXECUTABLE "${CMAKE_CXX_LINK_EXECUTABLE} -ldl")

add_executable(mach lib/glad.c src/MachApplication.cpp src/graphics/window/RenderWindow.cpp src/graphics/window/RenderWindow.hpp src/graphics/window/OpenGLWindow.cpp src/graphics/window/OpenGLWindow.hpp src/auxiliary/Constants.hpp src/io/input/KeyInput.cpp src/io/input/KeyInput.hpp src/io/input/MouseInput.cpp src/io/input/MouseInput.hpp src/MachApplication.hpp src/auxiliary/logging/Logger.cpp src/auxiliary/logging/Logger.hpp src/math/linalg/Vector/Vector.hpp src/math/linalg/Vector/Vector2.hpp src/math/linalg/Vector/Vector3.hpp src/math/linalg/Vector/Vector4.hpp src/math/linalg/LinAlgTypes.hpp src/math/linalg/Matrix/Matrix.hpp src/math/linalg/Vector/VectorTraits.hpp src/math/linalg/Quaternion.hpp src/math/util/NumberTraits.hpp src/math/linalg/Rotations.hpp src/math/linalg/Matrix/RotationMatrix.hpp src/auxiliary/exceptions/NotImplemented.hpp src/math/util/MathUtils.hpp tests/math/LinearAlgebraTests.hpp tests/TestRunner.hpp src/auxiliary/MachAssertion.hpp src/auxiliary/logging/LogUtils.hpp src/auxiliary/time/Timer.cpp src/auxiliary/time/Timer.hpp)

# Sets a base path for the includes so that they can be used in the same way as in Visual Studio/Codeblocks
set(BASEPATH "${CMAKE_SOURCE_DIR}/src")
include_directories("${BASEPATH}")


# Fix(es) for platform specific problems
if (APPLE)
    exec_program(uname ARGS -v OUTPUT_VARIABLE DARWIN_VERSION)
    string(REGEX MATCH "[0-9]+" DARWIN_VERSION ${DARWIN_VERSION})
    message(STATUS "OSX Version=${DARWIN_VERSION}")
    if (DARWIN_VERSION GREATER 17)
        message(STATUS "Running on OSX Mojave or higher, adding /usr/local/lib to link directories")
        # Fix linking on 10.14+. See https://stackoverflow.com/questions/54068035
        link_directories(/usr/local/lib)
    endif ()
endif ()


# Setting up PkgConfig
find_package(PkgConfig REQUIRED)

# Finding and including GLAD
target_include_directories(mach PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/include/")

# Finding and linking GLFW3
find_package(glfw3 3.3 REQUIRED)
if (GLFW3_FOUND)
    message(STATUS "Found GLFW 3, Including and Linking now")
    target_link_libraries(mach glfw)
endif (GLFW3_FOUND)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/modules/")

# Finding and linking OpenGL
find_package(OpenGL REQUIRED)
if (OPENGL_FOUND)
    message(STATUS "Found OpenGL, Including and Linking now")
    target_include_directories(mach PUBLIC ${OPENGL_INCLUDE_DIR})
    target_link_libraries(mach ${OPENGL_gl_LIBRARY})
endif (OPENGL_FOUND)