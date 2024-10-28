
cmake_minimum_required(VERSION 3.5)

project(duiduipeng)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_CXX_FLAGS_DEBUG "-g -O0 -fsanitize=address")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")


find_package(Threads REQUIRED)

add_executable(duiduipeng src/duiduipeng.cpp)
target_link_libraries(duiduipeng PRIVATE Threads::Threads)

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    message("Debug mode")
    target_compile_definitions(duiduipeng PRIVATE "DEBUG")
else()
    message("Release mode")
endif()

install(TARGETS duiduipeng DESTINATION bin)