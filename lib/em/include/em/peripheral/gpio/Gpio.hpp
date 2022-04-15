#pragma once

#include <cstdint>

#include "em/core/RegisterHandle.hpp"

namespace EM::Peripheral::Gpio
{

struct Gpio
{
    constexpr Gpio(const std::uintptr_t address) noexcept
        : outRegister{address + 0x504}, dirRegister{address + 0x514} 
    {}

    EM::Core::RegisterHandle<std::uint32_t> outRegister;
    EM::Core::RegisterHandle<std::uint32_t> dirRegister;
};

}