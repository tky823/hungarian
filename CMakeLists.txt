cmake_minimum_required(VERSION 3.16)

project(hungarian LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(hungarian
    src/hungarian.cpp
)

target_include_directories(hungarian
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
)

add_executable(benchmark_hungarian
    benchmarks/benchmark_hungarian.cpp
)

target_link_libraries(benchmark_hungarian
    PRIVATE hungarian
)
