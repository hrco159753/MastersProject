#include <Benchmark.hpp>

#include <cstdint>

namespace Benchmark::Em {

void run() noexcept {
  for (std::uint32_t counter{0}; counter < Benchmark::kNumberOfRepeat; ++counter) {
    asm volatile("");
  }
}
} // namespace Benchmark::Em