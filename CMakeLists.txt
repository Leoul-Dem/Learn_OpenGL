cmake_minimum_required(VERSION 3.20)

project(Learn_OpenGL LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(Learn_OpenGL
    main.cpp
)

if(WIN32)
    # GLM
    add_subdirectory("${CMAKE_CURRENT_LIST_DIR}/libraries/Windows/GLM" SYSTEM)

    # GLEW
    add_library(GLEW SHARED IMPORTED)
    set_target_properties(GLEW PROPERTIES
        IMPORTED_IMPLIB
            "${CMAKE_CURRENT_LIST_DIR}/libraries/Windows/GLEW/lib/Release/x64/glew32.lib"

        IMPORTED_LOCATION
            "${CMAKE_CURRENT_LIST_DIR}/libraries/Windows/GLEW/bin/Release/x64/glew32.dll"

        INTERFACE_INCLUDE_DIRECTORIES
            "${CMAKE_CURRENT_LIST_DIR}/libraries/Windows/GLEW/include"
    )

    # SDL3
    add_library(SDL3 STATIC IMPORTED)
    set_target_properties(SDL3 PROPERTIES
        IMPORTED_LOCATION
            "${CMAKE_CURRENT_LIST_DIR}/libraries/Windows/SDL3/lib/x64/SDL3.lib"

        INTERFACE_INCLUDE_DIRECTORIES
            "${CMAKE_CURRENT_LIST_DIR}/libraries/Windows/SDL3/include"
    )

    # GLFW
    add_library(GLFW SHARED IMPORTED)
    set_target_properties(GLFW PROPERTIES
        IMPORTED_IMPLIB
            "${CMAKE_CURRENT_LIST_DIR}/libraries/Windows/GLFW/lib/glfw3.lib"

        IMPORTED_LOCATION
            "${CMAKE_CURRENT_LIST_DIR}/libraries/Windows/GLFW/lib/glfw3.dll"

        INTERFACE_INCLUDE_DIRECTORIES
            "${CMAKE_CURRENT_LIST_DIR}/libraries/Windows/GLFW/include"
    )

    find_package(OpenGL REQUIRED)

    target_link_libraries(Learn_OpenGL PRIVATE GLFW SDL3 GLEW OpenGL::GL glm::glm)

    # Copy required DLLs next to Learn_OpenGL.exe
    add_custom_command(TARGET Learn_OpenGL POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${CMAKE_CURRENT_LIST_DIR}/libraries/GLEW/bin/Release/x64/glew32.dll"
            "$<TARGET_FILE_DIR:Learn_OpenGL>"

        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${CMAKE_CURRENT_LIST_DIR}/libraries/GLFW/lib/glfw3.dll"
            "$<TARGET_FILE_DIR:Learn_OpenGL>"
    )
elseif(UNIX AND NOT APPLE)
    # GLM
    add_subdirectory("${CMAKE_CURRENT_LIST_DIR}/libraries/Windows/GLM" SYSTEM)

    find_package(OpenGL REQUIRED)
    find_package(GLEW REQUIRED)
    find_package(glfw3 REQUIRED)
    find_package(SDL3 REQUIRED CONFIG)

    target_link_libraries(${PROJECT_NAME} PRIVATE
        OpenGL::GL
        GLEW::GLEW
        glfw
        SDL3::SDL3
        glm::glm
    )
endif()

