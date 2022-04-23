
function(add_flashable_target TARGET_NAME)
    add_custom_target(${TARGET_NAME}-flash
            DEPENDS ${TARGET_NAME}
            COMMAND ${NRFJPROG_EXE} -f nrf52 --program $<TARGET_FILE:${TARGET_NAME}> --sectoranduicrerase --verify --reset
            )
endfunction()
