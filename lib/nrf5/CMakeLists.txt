cmake_minimum_required(VERSION 3.0)

set(PROJECT_NAME "nrf5")

if(NOT DEFINED NRF_TARGET)
    message(FATAL_ERROR "NRF_TARGET needs to be defined")
endif()

if(NOT DEFINED NRF_CONFIG_DIR)
    message(FATAL_ERROR "NRF_CONFIG needs to be defined")
endif()

project(${PROJECT_NAME} LANGUAGES CXX C ASM)

add_library(${PROJECT_NAME} STATIC)
add_library(${PROJECT_NAME}::${PROJECT_NAME} ALIAS ${PROJECT_NAME})

target_sources(${PROJECT_NAME}
        PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}/modules/nrfx/drivers/src/nrfx_timer.c
)
target_include_directories(${PROJECT_NAME}
        PUBLIC
            ${CMAKE_CURRENT_SOURCE_DIR}/modules/nrfx/drivers/include
            ${CMAKE_CURRENT_SOURCE_DIR}/modules/nrfx
            ${CMAKE_CURRENT_SOURCE_DIR}/modules/nrfx/mdk
            ${CMAKE_CURRENT_SOURCE_DIR}/components/libraries/log
            ${CMAKE_CURRENT_SOURCE_DIR}/components/libraries/util
            ${CMAKE_CURRENT_SOURCE_DIR}/components/drivers_nrf/nrf_soc_nosd
            ${CMAKE_CURRENT_SOURCE_DIR}/components/toolchain/cmsis/include
            ${NRF_CONFIG_DIR}
)
target_compile_definitions(${PROJECT_NAME}
        PUBLIC
            -D${NRF_TARGET}
)
target_compile_options(${PROJECT_NAME}
    PRIVATE
        -Wno-sign-conversion
        -ggdb3
        -O0
        -Wno-format
)