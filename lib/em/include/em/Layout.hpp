#pragma once

#include "em/Config.hpp"

#include "em/peripheral/gpio/Gpio.hpp"

namespace EM::Layout
{

namespace Gpio
{
    static constinit EM::Peripheral::Gpio::Gpio Port[2] { {EM::Config::kGpioPort0Address}, {EM::Config::kGpioPort1Address} };
}

} // namespace EM::Layout
