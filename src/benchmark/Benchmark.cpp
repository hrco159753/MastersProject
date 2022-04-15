#include "benchmark/Benchmark.hpp"

namespace Benchmark {
void warmup(const std::uint32_t cycleNumber) noexcept {
  for (std::uint32_t cycle{0}; cycle < cycleNumber; ++cycle) {
    asm volatile("");
  }
}

Benchmark::Result runSingle(Stopwatch &stopwatch, uint32_t numberOfRepeats,
                   void (*benchmark)()) noexcept {

  stopwatch.reset();
  stopwatch.start();
  for (std::remove_const_t<decltype(numberOfRepeats)> index{0};
       index < numberOfRepeats; ++index) {
    benchmark();
  }
  stopwatch.stop();

  const auto elapsedTime{stopwatch.getElapsedTime()};
  const Benchmark::Result returnValue{elapsedTime, numberOfRepeats};

  return returnValue;
}
} // namespace Benchmark