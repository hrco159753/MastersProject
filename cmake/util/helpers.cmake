
function(add_flashable_target TARGET_NAME)
    add_custom_target(${TARGET_NAME}-flash
            DEPENDS ${TARGET_NAME}
            COMMAND ${NRFJPROG_EXE} -f nrf52 --program $<TARGET_FILE:${TARGET_NAME}> --sectoranduicrerase --verify --reset
            )
endfunction()

function(add_benchmark BENCHMARK_NAME SOURCE_DIR BENCHMARK_BASE_TARGET LINKER_DIR INCLUDE_DIR)
    add_library(${BENCHMARK_NAME}-em OBJECT)
    target_sources(${BENCHMARK_NAME}-em
        PRIVATE
            ${SOURCE_DIR}/em/src/main.cpp
    )
    target_include_directories(${BENCHMARK_NAME}-em
        PRIVATE
            ${INCLUDE_DIR}/em
            ${INCLUDE_DIR}/../config/benchmark
    )
    target_link_libraries(${BENCHMARK_NAME}-em
        PRIVATE
            ${BENCHMARK_BASE_TARGET}
    )

    add_library(${BENCHMARK_NAME}-nrf OBJECT)
    target_sources(${BENCHMARK_NAME}-nrf
        PRIVATE
            ${SOURCE_DIR}/nrf/src/main.cpp
    )
    target_include_directories(${BENCHMARK_NAME}-nrf
        PRIVATE
            ${INCLUDE_DIR}/nrf
            ${INCLUDE_DIR}/../config/benchmark
    )
    target_link_libraries(${BENCHMARK_NAME}-nrf
        PRIVATE
            ${BENCHMARK_BASE_TARGET}
    )

    add_executable(${BENCHMARK_NAME})
    target_link_libraries(${BENCHMARK_NAME}
        PRIVATE
            ${BENCHMARK_NAME}-em
            ${BENCHMARK_NAME}-nrf
            SeggerRtt::SeggerRtt
    )
    target_link_options(${BENCHMARK_NAME}
        PRIVATE
            -T ${LINKER_DIR}/nrf52840_xxaa.ld
            -L ${LINKER_DIR}
    )
    add_flashable_target(${BENCHMARK_NAME})
endfunction()

