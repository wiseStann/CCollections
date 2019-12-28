cmake_minimum_required(VERSION 3.10)

project(Collections VERSION 1.1.0)

set(CMAKE_DISABLE_IN_SOURCE_BUILD ON)
enable_language(C)

set(CFLAGS "-Wall -Werror")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${CFLAGS}")

add_subdirectory(src)
