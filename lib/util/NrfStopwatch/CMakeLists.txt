cmake_minimum_required(VERSION 3.0)

project(NrfStopwatch LANGUAGES C CXX)

add_library(${PROJECT_NAME} STATIC)
add_library(${PROJECT_NAME}::${PROJECT_NAME} ALIAS ${PROJECT_NAME})
target_sources(${PROJECT_NAME}
        PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}/src/Stopwatch.cpp
)
target_include_directories(${PROJECT_NAME}
        PUBLIC
            ${CMAKE_CURRENT_SOURCE_DIR}/include
)
target_link_libraries(${PROJECT_NAME}
        PRIVATE
            nrf5::nrf5
            SeggerRtt::SeggerRtt
)
target_compile_options(${PROJECT_NAME}
        PRIVATE
            -Wno-volatile
)