cmake_minimum_required(VERSION 4.1)

project(oscgui
        VERSION 0.1
        LANGUAGES C CXX
)

# =========================
# 基本编译选项
# =========================
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)  # 禁用编译器扩展，提高可移植性

# =========================
# 第三方库：GLFW
# =========================
# 必须提前设置，否则 GLFW 会编译示例和文档，浪费大量时间
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)

add_subdirectory(third_party/glfw)

# =========================
# oscgui 静态库（最终对外库）
# =========================

add_library(oscgui STATIC
        src/based.cpp
        src/components.cpp
        src/gui.cpp
        src/renderer.cpp

        third_party/glad/src/gl.c
        include/oscgui/oscgui_gui.cpp
        include/oscgui/oscgui_gui.h
        include/oscgui/oscgui_types.h
        include/oscgui/oscgui_components.cpp
        include/oscgui/oscgui_components.h
)

# 启用有用的编译警告（强烈建议）
if(MSVC)
    target_compile_options(oscgui PRIVATE /W4)
else()
    target_compile_options(oscgui PRIVATE -Wall -Wextra -Wpedantic)
endif()

# oscgui 的 include 边界（非常关键）
# 头文件管理（改进版）
target_include_directories(oscgui
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>  # 构建时路径
        $<INSTALL_INTERFACE:include>  # 安装后路径（为 make install 准备）
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
        ${CMAKE_CURRENT_SOURCE_DIR}/third_party/glad/include
)

# 平台相关的 OpenGL 链接
if(WIN32)
    target_link_libraries(oscgui PRIVATE glfw opengl32)
else()
    find_package(OpenGL REQUIRED)
    target_link_libraries(oscgui PRIVATE glfw OpenGL::GL)
endif()

# =========================
# oscgui_exe（你自己的 C++ OpenGL 实验程序）
# =========================
add_executable(oscgui_exe EXCLUDE_FROM_ALL
        src/main.cpp
        src/gui.h
        src/renderer.h
)

# oscgui_exe 是“特权程序”，可以直接用 OpenGL / glad
target_link_libraries(oscgui_exe
        PRIVATE
        oscgui
        glfw
        opengl32
)

target_include_directories(oscgui_exe
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/third_party/glad/include
        ${CMAKE_CURRENT_SOURCE_DIR}/third_party/linmath
)

# =========================
# oscgui_demo（纯 C，用户视角测试）
# =========================
add_executable(oscgui_demo EXCLUDE_FROM_ALL
        examples/demo.c
)

target_link_libraries(oscgui_demo
        PRIVATE
        oscgui
)

# =========================
# 资源拷贝（shader）
# =========================
add_custom_command(TARGET oscgui_exe POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/shader
        $<TARGET_FILE_DIR:oscgui_exe>/shader
        COMMENT "Copying shaders for oscgui_exe"
)

add_custom_command(TARGET oscgui_demo POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/shader
        $<TARGET_FILE_DIR:oscgui_demo>/shader
        COMMENT "Copying shaders for oscgui_demo"
)

# =========================
# 安装配置（发布包）
# =========================

install(
        TARGETS oscgui
        ARCHIVE DESTINATION lib
)

install(
        DIRECTORY
        ${CMAKE_CURRENT_SOURCE_DIR}/include/oscgui
        DESTINATION
        include
)