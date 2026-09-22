cmake_minimum_required(VERSION 3.16)
project(seminar1 CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

add_compile_options(-Wall -Wextra -Wpedantic)

add_executable(demo_pipeline
    pipeline/demo.cpp
    pipeline/mathutils.cpp)
target_include_directories(demo_pipeline PRIVATE pipeline)