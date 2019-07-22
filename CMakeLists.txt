cmake_minimum_required(VERSION 3.14)
project(mach)

set(CMAKE_CXX_STANDARD 17)

include(.conan/conanbuildinfo.cmake)

# NO_OUTPUT_DIRS is there to prevent conan from setting the output directory within cmake-build-debug to bin/mach instead of just mach
#conan_basic_setup(NO_OUTPUT_DIRS)
conan_basic_setup()


# Adding libdl, which is a dependency for GLAD on non-windows platforms and may not be recognized otherwise
set(CMAKE_CXX_LINK_EXECUTABLE "${CMAKE_CXX_LINK_EXECUTABLE} -ldl")

add_executable(mach lib/glad.c
        src/MachApplication.cpp
        src/graphics/renderer/window/RenderWindow.cpp
        src/graphics/renderer/window/RenderWindow.hpp
        src/graphics/renderer/window/OpenGLWindow.cpp
        src/graphics/renderer/window/OpenGLWindow.hpp
        src/auxiliary/Constants.hpp
        src/io/input/KeyInput.cpp
        src/io/input/KeyInput.hpp
        src/io/input/MouseInput.cpp
        src/io/input/MouseInput.hpp
        src/MachApplication.hpp
        src/auxiliary/logging/Logger.cpp
        src/auxiliary/logging/Logger.hpp
        src/math/linalg/Vector.hpp
        src/math/linalg/LinAlgTypes.hpp
        src/math/linalg/Matrix/Matrix.hpp
        src/math/linalg/Quaternion.hpp
        src/math/util/NumberTraits.hpp
        src/math/linalg/Rotations.hpp
        src/math/linalg/Matrix/RotationMatrix.hpp
        src/auxiliary/exceptions/NotImplemented.hpp
        src/math/util/MathUtils.hpp
        tests/LinearAlgebraTests.hpp
        tests/TestRunner.hpp
        src/auxiliary/MachAssertion.hpp
        src/auxiliary/logging/LogUtils.hpp
        src/auxiliary/time/Timer.hpp
        src/auxiliary/time/TimeUtils.hpp
        src/math/linalg/Matrix/ScaleMatrix.hpp
        src/graphics/renderer/shaders/OpenGLShader.hpp
        src/graphics/renderer/debug/OpenGLDebug.hpp
        src/graphics/renderer/Renderer.cpp
        src/graphics/renderer/Renderer.hpp
        src/graphics/renderer/OpenGLRenderer.cpp
        src/graphics/renderer/OpenGLRenderer.hpp
        src/io/files/FileIO.hpp
        src/auxiliary/parsing/ParserUtils.hpp
        src/auxiliary/VectorUtils.hpp
        src/graphics/renderer/model/Mesh.hpp
        src/graphics/renderer/texture/OpenGLTexture.hpp
        src/auxiliary/Properties.hpp
        src/graphics/renderer/model/Model.hpp
        src/graphics/renderer/model/Vertex.hpp
        src/graphics/renderer/material/Texture.hpp
        src/caching/AssetCache.hpp
        src/math/linalg/Matrix/MatrixUtils.hpp
        src/core/Scene/Camera.hpp
        src/math/linalg/TransformCompound.hpp
        src/auxiliary/Memory.hpp
        src/core/Scene/SceneNode.hpp
        src/core/Scene/Behaviour/SceneBehaviour.hpp src/core/Scene/SceneHierarchy.hpp tests/CoreEngineTests.hpp)

target_compile_options(mach PRIVATE -fdeclspec)

# Sets a base path for the includes so that they can be used in the same way as in Visual Studio/Codeblocks
set(BASEPATH "${CMAKE_SOURCE_DIR}/src")
include_directories("${BASEPATH}")

# Copies the res folder to the build folder
file(COPY res DESTINATION ${CMAKE_BINARY_DIR})

# Setting up PkgConfig
find_package(PkgConfig REQUIRED)

# Finding and including GLAD
target_include_directories(mach PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/include/")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/modules/")

# Finding and linking OpenGL
find_package(OpenGL REQUIRED)
if (OPENGL_FOUND)
    message(STATUS "Found OpenGL, Including and Linking now")
    target_include_directories(mach PUBLIC ${OPENGL_INCLUDE_DIR})
    target_link_libraries(mach ${OPENGL_gl_LIBRARY})
elseif (NOT OPENGL_FOUND)
    message(FATAL_ERROR "Could not find OpenGL")
endif (OPENGL_FOUND)


target_link_libraries(mach ${CONAN_LIBS})