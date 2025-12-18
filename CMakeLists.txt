cmake_minimum_required(VERSION 4.1)
project(OpenGL_C_GUI)

set(CMAKE_CXX_STANDARD 20)

include(FetchContent)

FetchContent_Declare(
        glfw
        GIT_REPOSITORY https://github.com/glfw/glfw.git
        GIT_TAG 3.4
)

FetchContent_MakeAvailable(glfw)

add_executable(OpenGL_C_GUI
        src/main.cpp
        src/gl.c
)

file(COPY ${CMAKE_SOURCE_DIR}/shader DESTINATION ${CMAKE_BINARY_DIR})

target_link_libraries(OpenGL_C_GUI glfw opengl32)
target_include_directories(OpenGL_C_GUI PRIVATE include)