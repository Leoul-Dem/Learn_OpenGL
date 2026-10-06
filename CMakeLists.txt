cmake_minimum_required(VERSION 3.20)

project(Learn_OpenGL LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(Learn_OpenGL
    main.cpp
)

# GLEW SETUP

add_library(GLEW SHARED IMPORTED)

if(WIN32)
set_target_properties(GLEW PROPERTIES
    IMPORTED_IMPLIB
        "${CMAKE_CURRENT_LIST_DIR}/libraries/GLEW/lib/Release/x64/glew32.lib"

    IMPORTED_LOCATION
        "${CMAKE_CURRENT_LIST_DIR}/libraries/GLEW/bin/Release/x64/glew32.dll"

    INTERFACE_INCLUDE_DIRECTORIES
        "${CMAKE_CURRENT_LIST_DIR}/libraries/GLEW/include"
)
endif()

# SDL3 SETUP

add_library(SDL3 STATIC IMPORTED)

if(WIN32)
set_target_properties(SDL3 PROPERTIES
    IMPORTED_LOCATION
        "${CMAKE_CURRENT_LIST_DIR}/libraries/SDL3/lib/x64/SDL3.lib"

    INTERFACE_INCLUDE_DIRECTORIES
        "${CMAKE_CURRENT_LIST_DIR}/libraries/SDL3/include"
)
endif()

# GLFW SETUP

add_library(GLFW SHARED IMPORTED)

if(WIN32)
set_target_properties(GLFW PROPERTIES
    IMPORTED_IMPLIB
        "${CMAKE_CURRENT_LIST_DIR}/libraries/GLFW/lib/glfw3.lib"

    IMPORTED_LOCATION
        "${CMAKE_CURRENT_LIST_DIR}/libraries/GLFW/lib/glfw3.dll"

    INTERFACE_INCLUDE_DIRECTORIES
        "${CMAKE_CURRENT_LIST_DIR}/libraries/GLFW/include"
)
endif()

find_package(OpenGL REQUIRED)

target_link_libraries(Learn_OpenGL PRIVATE GLFW SDL3 GLEW OpenGL::GL)

# Copy required DLLs next to Learn_OpenGL.exe
add_custom_command(TARGET Learn_OpenGL POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${CMAKE_CURRENT_LIST_DIR}/libraries/GLEW/bin/Release/x64/glew32.dll"
        "$<TARGET_FILE_DIR:Learn_OpenGL>"

    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${CMAKE_CURRENT_LIST_DIR}/libraries/GLFW/lib/glfw3.dll"
        "$<TARGET_FILE_DIR:Learn_OpenGL>"
)