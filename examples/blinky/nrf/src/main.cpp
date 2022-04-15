#include <Benchmark.hpp>

#include <cstdint>

namespace Benchmark::Nrf {
void run() noexcept {
  for (std::uint32_t counter{0}; counter < kNumberOfRepeat; ++counter) {
    asm volatile("");
  }
}
} // namespace Benchmark::Nrf
