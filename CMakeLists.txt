cmake_minimum_required(VERSION 3.16)

project(Learn_OpenGL LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(Learn_OpenGL main.cpp)

include(GNUInstallDirs)
install(TARGETS Learn_OpenGL
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
