cmake_minimum_required(VERSION 3.0 FATAL_ERROR)
cmake_policy(VERSION 3.0)

set (CMAKE_VERBOSE_MAKEFILE 1)

set(NAME Drawlines)
project(${NAME})

#add -Wconversion
add_definitions(-Wall -std=c++17 -O3 -Wextra -Winline -Wreturn-type -Wuninitialized -Winit-self -Werror -Wno-unused-parameter -Wno-unused-function)

# Bring the shared libraries into the project (for the linker and loader)
set(PROJECT_LINK_LIBS libSDL2.so)
link_directories(/usr/lib/libSDL2.so)

# Bring the headers into the project (for the compiler)
include_directories(/usr/include/SDL2/
                    CMAKE_SOURCE_DIR/src)

# The file(GLOB...) allows for wildcard additions:
file(GLOB SOURCES "src/*.cpp")

add_executable(drawlines ${SOURCES})
target_link_libraries(drawlines ${PROJECT_LINK_LIBS})
