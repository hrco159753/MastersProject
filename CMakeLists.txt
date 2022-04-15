cmake_minimum_required(VERSION 3.0)

set(CMAKE_EXECUTABLE_SUFFIX_CXX ".elf")
set(BENCHMARK_BASE_NAME "BenchmarkBase")
set(BENCHMARK_BACKEND_NAME "BenchmarkBackend")

project(${BENCHMARK_BASE_NAME} LANGUAGES CXX C ASM)

add_library(${BENCHMARK_BACKEND_NAME} STATIC)
target_sources(${BENCHMARK_BACKEND_NAME}
    PRIVATE
		${CMAKE_CURRENT_SOURCE_DIR}/src/benchmark/Stopwatch.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/src/benchmark/Benchmark.cpp
)

add_library(${BENCHMARK_BASE_NAME} STATIC)
target_sources(${BENCHMARK_BASE_NAME}
	PRIVATE
		${CMAKE_CURRENT_SOURCE_DIR}/startup/src/gcc_startup_nrf52840.S
		${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
)

######################## Dependencies ###########################
# EM
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/lib/em)

# NRF5
set(NRF_TARGET NRF52840_XXAA)
set(NRF_CONFIG_DIR ${CMAKE_CURRENT_SOURCE_DIR}/config/nrf5)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/lib/nrf5)

# SeggerRtt
add_subdirectory(lib/util/segger-rtt)

######################## Building ###########################
target_link_libraries(${BENCHMARK_BACKEND_NAME}
    PUBLIC
        EmbedModernize::EmbedModernize
		nrf5::nrf5
)
target_include_directories(${BENCHMARK_BACKEND_NAME}
	PRIVATE
		${CMAKE_CURRENT_SOURCE_DIR}/include
		${CMAKE_CURRENT_SOURCE_DIR}/config/benchmark
)
target_compile_options(${BENCHMARK_BACKEND_NAME}
	PRIVATE
		-Wno-volatile
)

target_link_libraries(${BENCHMARK_BASE_NAME}
	PUBLIC
		${BENCHMARK_BACKEND_NAME}
		SeggerRtt::SeggerRtt
)
target_include_directories(${BENCHMARK_BASE_NAME}
	PRIVATE
		${CMAKE_CURRENT_SOURCE_DIR}/config/benchmark
		${CMAKE_CURRENT_SOURCE_DIR}/include
)


####################### Benchmarks ##########################
include(cmake/util/helpers.cmake)

add_benchmark(test_benchmark
		${CMAKE_CURRENT_SOURCE_DIR}/examples/blinky
		${BENCHMARK_BASE_NAME}
		${CMAKE_CURRENT_SOURCE_DIR}/startup/linker
		${CMAKE_CURRENT_SOURCE_DIR}/include)

