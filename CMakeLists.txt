cmake_minimum_required(VERSION 3.16)
project(BlackHoleVisualizer VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Determine build type
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

# Find packages
find_package(OpenGL REQUIRED)
find_package(glfw3 3.3 REQUIRED)

# Include directories
include_directories(${CMAKE_SOURCE_DIR}/include)
include_directories(${OPENGL_INCLUDE_DIR})

# Add subdirectories
add_subdirectory(external)

# Source files
set(SOURCES
    src/main.cpp
    src/core/Window.cpp
    src/core/Camera.cpp
    src/renderer/ShaderProgram.cpp
    src/renderer/Renderer.cpp
    src/physics/KerrBlackHole.cpp
    src/physics/RayTracer.cpp
)

# Create executable
add_executable(BlackHoleVisualizer ${SOURCES})

# Link libraries
target_link_libraries(BlackHoleVisualizer 
    PRIVATE
    OpenGL::GL
    glfw
    glad
    glm
)

# Set output directory
set_target_properties(BlackHoleVisualizer PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

# Shader files (copy to build directory)
add_custom_target(copy_shaders ALL
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/shaders
    ${CMAKE_BINARY_DIR}/shaders
    COMMENT "Copying shader files..."
)

add_dependencies(BlackHoleVisualizer copy_shaders)

# Platform-specific settings
if(WIN32)
    set_target_properties(BlackHoleVisualizer PROPERTIES
        SUBSYSTEM WINDOWS
    )
endif()

# Compiler optimizations for Release
if(CMAKE_BUILD_TYPE MATCHES Release)
    if(MSVC)
        target_compile_options(BlackHoleVisualizer PRIVATE /O2 /W3)
    else()
        target_compile_options(BlackHoleVisualizer PRIVATE -O3 -march=native -Wall -Wextra)
    endif()
endif()

# Debug symbols
if(CMAKE_BUILD_TYPE MATCHES Debug)
    if(MSVC)
        target_compile_options(BlackHoleVisualizer PRIVATE /Zi)
    else()
        target_compile_options(BlackHoleVisualizer PRIVATE -g)
    endif()
endif()

# Print build info
message(STATUS "Build Type: ${CMAKE_BUILD_TYPE}")
message(STATUS "C++ Standard: ${CMAKE_CXX_STANDARD}")
message(STATUS "OpenGL: ${OPENGL_LIBRARY}")
