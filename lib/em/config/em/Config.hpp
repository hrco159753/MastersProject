#pragma once

#include <cstdint>

namespace EM::Config
{

static constexpr std::size_t frequency{64'000'000};
static constexpr std::uintptr_t kGpioPort0Address{0x5000'0000};
static constexpr std::uintptr_t kGpioPort1Address{0x5000'0300};
static constexpr std::uintptr_t kNvicAddresss{0xE000E100};

}