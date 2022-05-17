#include <cstdio>

#include <Benchmark.hpp>
#include <Config.hpp>
#include <Stopwatch.hpp>
#include <StopwatchConcept.hpp>

static const Benchmark::BenchmarkDescriptor descriptor{
    Base::name(), Base::repeat(), &Base::run};

int main() {
  Benchmark::Meta::Stopwatch auto stopwatch{Stopwatch::Stopwatch{}};

  if (not stopwatch.init()) {
    std::printf("Can't init stopwatch!");
    return 1;
  }

  const auto [totalTime]{Benchmark::benchmark(stopwatch, descriptor)};
  const auto [name, cycles, dummy]{descriptor};

  std::printf(
      "Name: %10s\n\tTotal time: %luus\n\tCycles: %lu\n\tAverage: %luus\n",
      name.data(), static_cast<std::uint32_t>(totalTime.count()),
      static_cast<std::uint32_t>(cycles),
      static_cast<std::uint32_t>(totalTime.count() / cycles));
}