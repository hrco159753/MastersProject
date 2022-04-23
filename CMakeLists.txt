cmake_minimum_required(VERSION 3.0)

set(CMAKE_EXECUTABLE_SUFFIX_CXX ".elf")
project(base LANGUAGES CXX C ASM)

######################## Dependencies ###########################
# EM
# add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/lib/em)

# NRF5
set(NRF_TARGET NRF52840_XXAA)
set(NRF_CONFIG_DIR ${CMAKE_CURRENT_SOURCE_DIR}/config/nrf5)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/lib/nrf5)

# SeggerRtt
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/lib/util/segger-rtt)

# Benchmark
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/lib/util/benchmark)

# Benchmark
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/lib/util/NrfStopwatch)

################################################################

add_library(${PROJECT_NAME} STATIC)
add_library(${PROJECT_NAME}::${PROJECT_NAME} ALIAS ${PROJECT_NAME})
target_sources(${PROJECT_NAME}
        PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/startup/src/gcc_startup_nrf52840.S
            ${CMAKE_CURRENT_SOURCE_DIR}/startup/src/system.cpp
        )
target_link_libraries(${PROJECT_NAME}
        PRIVATE
            benchmark::benchmark
            NrfStopwatch::NrfStopwatch
        )
target_include_directories(${PROJECT_NAME}
        PUBLIC
            ${CMAKE_CURRENT_SOURCE_DIR}/include
        )
target_link_options(${PROJECT_NAME}
        INTERFACE
            -T ${CMAKE_CURRENT_SOURCE_DIR}/startup/linker/nrf52840_xxaa.ld
            -L ${CMAKE_CURRENT_SOURCE_DIR}/startup/linker
        )

######################### Examples ###########################

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/examples)
