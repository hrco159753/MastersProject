cmake_minimum_required(VERSION 3.21)
project(benchmark LANGUAGES CXX)

add_library(benchmark STATIC)
add_library(benchmark::benchmark ALIAS benchmark)

target_compile_features(benchmark
        PUBLIC
            cxx_std_20
)
target_sources(benchmark
        PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}/src/Benchmark.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/src/Warmup.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/src/PolymorphicStopwatch.cpp
)
target_include_directories(benchmark
        PUBLIC
            ${CMAKE_CURRENT_SOURCE_DIR}/include/public
        PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}/include/private
)
