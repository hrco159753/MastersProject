#include "em/core/Delay.hpp"

#include <cstdint>

namespace EM::Core
{

void delayOneSecond() noexcept
{
	static constexpr std::size_t numberOfInstructions{6'400'000};

	for(std::size_t i{0}; i < numberOfInstructions; ++i)
	{
		asm volatile ("nop");
	}
}

} // namespace EM::Core
