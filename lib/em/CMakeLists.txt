cmake_minimum_required(VERSION 3.0)

set(PROJECT_NAME "EmbedModernize")

project(${PROJECT_NAME} LANGUAGES CXX C ASM)

add_library(${PROJECT_NAME} STATIC)
add_library(${PROJECT_NAME}::${PROJECT_NAME} ALIAS ${PROJECT_NAME})

target_sources(${PROJECT_NAME}
	PRIVATE
		${CMAKE_CURRENT_SOURCE_DIR}/src/em/core/Delay.cpp
)
target_compile_options(${PROJECT_NAME}
	PRIVATE
		-O0
		-ggdb3
)
target_include_directories(${PROJECT_NAME}
	PUBLIC
		${CMAKE_CURRENT_SOURCE_DIR}/include
		${CMAKE_CURRENT_SOURCE_DIR}/config
)

