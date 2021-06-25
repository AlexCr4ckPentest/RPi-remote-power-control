cmake_minimum_required(VERSION 3.1)

project(rpc LANGUAGES C)

file(GLOB_RECURSE SRC ./src/*.c)
file(GLOB_RECURSE INC ./include/*.h)

include_directories(${INCLUDE_DIRECTORIES} ./include)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O2 -Wall -Wpedantic -Wextra")

add_executable(${PROJECT_NAME} rpc.c ${SRC} ${INC})
