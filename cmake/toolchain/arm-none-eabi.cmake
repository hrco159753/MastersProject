# Toolchain for arm-none-eabi.

set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR ARM)

# Set toolchain paths.
set(TOOLCHAIN_NAME arm-none-eabi)
set(TOOLCHAIN_GCC_FOLDER_PATH "/home/hrvoje/Programming/bin/gcc-arm-none-eabi-10.3-2021.10")

set(CMAKE_TRY_COMPILE_PLATFORM_VARIABLES TOOLCHAIN_GCC_FOLDER_PATH)
set(TOOLCHAIN_BIN_FOLDER_PATH "${TOOLCHAIN_GCC_FOLDER_PATH}/bin")

# Set up compilers.
set(CMAKE_C_COMPILER ${TOOLCHAIN_BIN_FOLDER_PATH}/${TOOLCHAIN_NAME}-gcc${TOOLCHAIN_EXT}
            CACHE INTERNAL "C compiler.")
set(CMAKE_CXX_COMPILER ${TOOLCHAIN_BIN_FOLDER_PATH}/${TOOLCHAIN_NAME}-g++${TOOLCHAIN_EXT}
            CACHE INTERNAL "C++ compiler.")
set(CMAKE_ASM_COMPILER ${TOOLCHAIN_BIN_FOLDER_PATH}/${TOOLCHAIN_NAME}-gcc${TOOLCHAIN_EXT}
            CACHE INTERNAL "ASM compiler.")
set(CMAKE_OBJCOPY_BIN ${TOOLCHAIN_BIN_FOLDER_PATH}/${TOOLCHAIN_NAME}-objcopy${TOOLCHAIN_EXT}
            CACHE INTERNAL "Objcopy executable.")
set(CMAKE_SIZE_BIN ${TOOLCHAIN_BIN_FOLDER_PATH}/${TOOLCHAIN_NAME}-size${TOOLCHAIN_EXT}
            CACHE INTERNAL "Size executable.")

find_program(NRFJPROG_EXE nrfjprog REQUIRED)

# Perform compiler test as a static library. This will impede the linker from running when testing
# for the validity of the toolchain. This is okay as this is a cross-compilation.
set(CMAKE_TRY_COMPILE_TARGET_TYPE "STATIC_LIBRARY")

set(LINKER_ASM_C_CXX_OPTIONS "-mthumb -mabi=aapcs -mcpu=cortex-m4 -mfloat-abi=hard -mfpu=fpv4-sp-d16 -fno-common -finline-small-functions -findirect-inlining"
        CACHE INTERNAL "Compile/link options for linker, assembler, C and C++ compiler.")
set(ASM_C_CXX_OPTIONS ""
        CACHE INTERNAL "Compile options for assembler, C and C++ compiler.")
set(ASM_OPTIONS ""
        CACHE INTERNAL "Compile options for assembler.")
set(C_OPTIONS "-std=c11"
        CACHE INTERNAL "Compile options for C compiler.")
set(C_CXX_OPTIONS "--specs=nano.specs -Wpedantic -Wextra -Wshadow=local -Wall -Wdouble-promotion -Wconversion -ffunction-sections -fdata-sections -fno-strict-aliasing -fshort-enums -fno-builtin -Wunknown-pragmas -Wswitch-enum"
        CACHE INTERNAL "Compile options for C and C++ compiler.")
set(CXX_OPTIONS "-std=c++20 -fconcepts-diagnostics-depth=5 -fno-exceptions -fno-rtti -fno-use-cxa-atexit"
        CACHE INTERNAL "Compile options for C++ compiler.")
set(LINKER_OPTIONS "-ffunction-sections -fdata-sections -Wl,--gc-sections --verbose"
        CACHE INTERNAL "Link options.")

set(CMAKE_ASM_FLAGS "${LINKER_ASM_C_CXX_OPTIONS} ${ASM_C_CXX_OPTIONS} ${ASM_OPTIONS}" CACHE INTERNAL "")
set(CMAKE_C_FLAGS "${LINKER_ASM_C_CXX_OPTIONS} ${ASM_C_CXX_OPTIONS} ${C_OPTIONS} ${C_CXX_OPTIONS}" CACHE INTERNAL "")
set(CMAKE_CXX_FLAGS "${LINKER_ASM_C_CXX_OPTIONS} ${ASM_C_CXX_OPTIONS} ${C_CXX_OPTIONS} ${CXX_OPTIONS}" CACHE INTERNAL "")
set(CMAKE_EXE_LINKER_FLAGS "${LINKER_ASM_C_CXX_OPTIONS} ${LINKER_OPTIONS}" CACHE INTERNAL "")
