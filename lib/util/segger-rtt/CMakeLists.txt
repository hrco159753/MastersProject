cmake_minimum_required(VERSION 3.0)

set(PROJECT_NAME "SeggerRtt")

project(${PROJECT_NAME} LANGUAGES C ASM)

add_library(${PROJECT_NAME} OBJECT)
add_library(${PROJECT_NAME}::${PROJECT_NAME} ALIAS ${PROJECT_NAME})

target_sources(${PROJECT_NAME}
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/RTT/SEGGER_RTT.c
        ${CMAKE_CURRENT_SOURCE_DIR}/Syscalls/SEGGER_RTT_Syscalls_GCC.c
)
target_include_directories(${PROJECT_NAME}
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/RTT
)
target_compile_definitions(${PROJECT_NAME}
    PRIVATE
)
target_compile_options(${PROJECT_NAME}
    PRIVATE
        -Wno-sign-conversion
        -ggdb3
        -O0
)