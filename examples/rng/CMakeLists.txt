cmake_minimum_required(VERSION 3.0)

project(rng LANGUAGES CXX C)

include(${CMAKE_SOURCE_DIR}/cmake/util/helpers.cmake)

set(NRF_POSTFIX "nrf")
set(EM_POSTFIX "em")

# Nrf
add_executable(${PROJECT_NAME}-${NRF_POSTFIX})
target_sources(${PROJECT_NAME}-${NRF_POSTFIX}
        PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}/nrf/main.c
)
target_link_libraries(${PROJECT_NAME}-${NRF_POSTFIX}
        PRIVATE
            base::base
            nrf5::nrf5
            SeggerRtt::SeggerRtt
)
add_flashable_target(${PROJECT_NAME}-${NRF_POSTFIX})

# Em
add_executable(${PROJECT_NAME}-${EM_POSTFIX})
target_sources(${PROJECT_NAME}-${EM_POSTFIX}
        PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}/em/main.cpp
)
target_link_libraries(${PROJECT_NAME}-${EM_POSTFIX}
        PRIVATE
            base::base
            EmbedModernize::EmbedModernize
            SeggerRtt::SeggerRtt
)
add_flashable_target(${PROJECT_NAME}-${EM_POSTFIX})
