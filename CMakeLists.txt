
cmake_minimum_required(VERSION 3.5)

project(duiduipeng)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(duiduipeng src/duiduipeng.cpp)

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    message("Debug mode")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -O0 -fsanitize=address")
    target_compile_definitions(duiduipeng PRIVATE "DEBUG")
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -O3")
    message("Release mode")
endif()

install(TARGETS duiduipeng DESTINATION bin)