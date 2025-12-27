cmake_minimum_required(VERSION 4.1)

project(oscgui
        VERSION 0.1
        LANGUAGES C CXX
)

if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
    set(CMAKE_INSTALL_PREFIX "${CMAKE_SOURCE_DIR}/" CACHE PATH "" FORCE)
endif()

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
        # 核心类型文件
        src/types.cpp
        include/oscgui_types.h
        src/extern/oscgui_types.cpp

        # GUI 相关文件
        src/gui.cpp
        include/oscgui_gui.h
        src/extern/oscgui_gui.cpp

        # 组件相关文件
        src/components.cpp
        include/oscgui_components.h
        src/extern/oscgui_components.cpp

        # 应用相关文件
        src/app.cpp
        include/oscgui_app.h
        src/extern/oscgui_app.cpp

        # 文本处理文件
        src/Text.cpp
        src/Text.h

        # 渲染器相关文件
        src/renderer.cpp
        src/renderer.h

        # 第三方库文件
        third_party/glad/src/gl.c
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
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
        ${CMAKE_CURRENT_SOURCE_DIR}/third_party/glad/include
        ${CMAKE_CURRENT_SOURCE_DIR}/third_party/linmath
        ${CMAKE_CURRENT_SOURCE_DIR}/third_party
)

# 平台相关的 OpenGL 链接
if(WIN32)
    target_link_libraries(oscgui
            PRIVATE
            glfw
            opengl32
    )
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
        src/renderer.cpp
        src/Text.cpp
        src/Text.h
        src/app.cpp
        src/app.h
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
        ${CMAKE_CURRENT_SOURCE_DIR}/third_party/glad/
        ${CMAKE_CURRENT_SOURCE_DIR}/third_party
)

# demo
add_executable(oscgui_demo EXCLUDE_FROM_ALL
        examples/demo.c
)

target_include_directories(oscgui_demo PRIVATE
        ${CMAKE_INSTALL_PREFIX}/include
)

target_link_directories(oscgui_demo PRIVATE
        ${CMAKE_INSTALL_PREFIX}/lib
)

target_link_libraries(oscgui_demo
        oscgui
)

# =========================
# 资源拷贝（shader）
# =========================
add_custom_command(TARGET oscgui_exe POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/img
        $<TARGET_FILE_DIR:oscgui_exe>/img
        COMMENT "Copying img for oscgui_exe"
)

add_custom_command(TARGET oscgui_exe POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/font
        $<TARGET_FILE_DIR:oscgui_exe>/font
        COMMENT "Copying fonts for oscgui_exe"
)

# =========================
# 安装配置（发布包）
# =========================

find_package(Threads REQUIRED)
target_link_libraries(oscgui PRIVATE Threads::Threads)

install(
        TARGETS oscgui
        ARCHIVE DESTINATION lib
)

install(
        DIRECTORY
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        DESTINATION
        /
)

install(
        DIRECTORY
        ${CMAKE_CURRENT_SOURCE_DIR}/font
        DESTINATION
        /
)

install(
        DIRECTORY
        ${CMAKE_CURRENT_SOURCE_DIR}/img
        DESTINATION
        /
)

install(TARGETS oscgui
        EXPORT oscguiTargets
        ARCHIVE DESTINATION lib
)

install(EXPORT oscguiTargets
        FILE oscguiTargets.cmake
        NAMESPACE oscgui::
        DESTINATION lib/cmake/oscgui
)


install(TARGETS glfw
        EXPORT oscguiTargets
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib
        RUNTIME DESTINATION bin
)

# =========================
# 库配置
# =========================

include(CMakePackageConfigHelpers)

write_basic_package_version_file(
        "${CMAKE_CURRENT_BINARY_DIR}/oscguiConfigVersion.cmake"
        VERSION ${PROJECT_VERSION}
        COMPATIBILITY SameMajorVersion
)

configure_package_config_file(
        "${CMAKE_CURRENT_SOURCE_DIR}/oscguiConfig.cmake.in"
        "${CMAKE_CURRENT_BINARY_DIR}/oscguiConfig.cmake"
        INSTALL_DESTINATION lib/cmake/oscgui
)

install(FILES
        "${CMAKE_CURRENT_BINARY_DIR}/oscguiConfig.cmake"
        "${CMAKE_CURRENT_BINARY_DIR}/oscguiConfigVersion.cmake"
        DESTINATION lib/cmake/oscgui
)