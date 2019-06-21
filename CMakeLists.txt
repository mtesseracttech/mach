cmake_minimum_required(VERSION 3.14)
project(mach)

set(CMAKE_CXX_STANDARD 17)

add_executable(mach lib/glad.c src/MachApplication.cpp src/graphics/window/RenderWindow.cpp src/graphics/window/RenderWindow.hpp src/graphics/window/OpenGLWindow.cpp src/graphics/window/OpenGLWindow.hpp src/auxiliary/Constants.hpp src/io/KeyInput.cpp src/io/KeyInput.hpp src/io/MouseInput.cpp src/io/MouseInput.hpp src/MachApplication.hpp src/auxiliary/LogHelper.cpp src/auxiliary/LogHelper.hpp src/math/linalg/Vector/Vector.hpp src/math/linalg/Vector/Vector2.hpp src/math/linalg/Vector/Vector3.hpp src/math/linalg/Vector/Vector4.hpp src/math/linalg/LinMatTypes.hpp src/math/linalg/Matrix/Matrix.hpp src/math/linalg/Vector/VectorTraits.hpp src/math/linalg/Quaternion.hpp src/math/util/NumberTraits.hpp src/math/linalg/Rotations.hpp src/math/linalg/Matrix/RotationMatrix.hpp src/math/linalg/Matrix/TransformMatrix.hpp src/math/linalg/Matrix/ScaleMatrix.hpp src/auxiliary/Exceptions.hpp src/math/util/MathUtils.hpp)

#Sets a base path for the includes so that they can be used in the same way as in Visual Studio/Codeblocks
set(BASEPATH "${CMAKE_SOURCE_DIR}/src")
include_directories("${BASEPATH}")

#Setting up PkgConfig

find_package(PkgConfig REQUIRED)

#Finding and including GLAD

target_include_directories(mach PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/include/")

#Finding and linking GLFW3

pkg_search_module(GLFW3 3.2 REQUIRED glfw3)
if (GLFW3_FOUND)
    message(STATUS "Found GLFW, Including and Linking now")
    include_directories(${GLFW3_INCLUDE_DIRS})
    target_link_libraries(mach ${GLFW3_STATIC_LIBRARIES})
endif (GLFW3_FOUND)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/modules/")

#Finding and linking OpenGL

find_package(OpenGL REQUIRED)


