#pragma once

#include <chrono>
#include <cstdint>
#include <string_view>

#include "em/Benchmark.hpp"
#include "nrf/Benchmark.hpp"

#include "benchmark/Stopwatch.hpp"

namespace Benchmark {
void warmup(std::uint32_t cycleNumber) noexcept;

struct Descriptor {
  const std::string_view benchmarkName;
  const std::uint32_t numberOfRepeats;
  void (*const runFunction)();
};

struct Result {
  std::chrono::microseconds total;
  std::uint32_t numberOfRepeats;
};
constexpr Result &operator+=(Result &b1,
                                      const Result &b2) noexcept {
  b1.total += b2.total;
  b1.numberOfRepeats += b2.numberOfRepeats;
  return b1;
}

Benchmark::Result runSingle(Stopwatch &stopwatch, std::uint32_t numberOfRepeats,
                   void (*benchmark)()) noexcept;

} // namespace Benchmark