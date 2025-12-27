cmake_minimum_required(VERSION 4.1)
project(oscgui_example CXX C)

set(CMAKE_C_STANDARD 11)

find_package(oscgui REQUIRED PATHS ${CMAKE_CURRENT_SOURCE_DIR}/install/lib/cmake/oscgui NO_DEFAULT_PATH)

add_executable(oscgui_example main.c)

target_link_libraries(oscgui_example PRIVATE oscgui::oscgui)

add_custom_command(TARGET oscgui_example POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/install/font
        $<TARGET_FILE_DIR:oscgui_example>/font
        COMMENT "Copying fonts for oscgui_example"
)

add_custom_command(TARGET oscgui_example POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/install/img
        $<TARGET_FILE_DIR:oscgui_example>/img
        COMMENT "Copying img for oscgui_example"
)