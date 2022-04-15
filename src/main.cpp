#include <array>
#include <cstdio>
#include <functional>

#include "Config.hpp"
#include "benchmark/Benchmark.hpp"
#include "benchmark/Stopwatch.hpp"

static void showBenchmarkResult(
    const std::pair<std::reference_wrapper<const Benchmark::Descriptor>,
                    std::reference_wrapper<const Benchmark::Result>> &pair) {
  const auto [name, dummy1, dummy2] = pair.first.get();
  const auto [elapsedTime, numberOfRepeats] = pair.second.get();

  std::printf("Benchmark: %s\n\tTotal: %luus\n\tAverage: %luus\n", name.data(),
              static_cast<std::uint32_t>(elapsedTime.count()),
              static_cast<std::uint32_t>(elapsedTime.count()) /
                  numberOfRepeats);
}

constexpr static std::uint32_t kNumberOfRepeats{5'000};
constexpr static std::uint32_t kWarmupCycles{10'000};
constexpr static std::array benchmarkDataArray{
    Benchmark::Descriptor{"Em", kNumberOfRepeats, &Benchmark::Em::run},
    Benchmark::Descriptor{"Nrf", kNumberOfRepeats, &Benchmark::Em::run}};
constinit static std::array<Benchmark::Result, benchmarkDataArray.size()>
    benchmarkResultArray{};

constinit static Benchmark::Stopwatch stopwatch{};
constinit static std::array benchmarks{
    std::pair{std::ref(benchmarkDataArray[0]),
              std::ref(benchmarkResultArray[0])},
    std::pair{std::ref(benchmarkDataArray[1]),
              std::ref(benchmarkResultArray[1])}};

int main() {
  if (not stopwatch.init()) {
    std::printf("Stopwatch not initialized!\n");
    return 1;
  }

  for (auto &benchmark : benchmarks) {
    const auto &[name, numberOfRepeats, runFunction] = benchmark.first.get();
    auto &benchmarkResult = benchmark.second.get();

    Benchmark::warmup(kWarmupCycles);

    benchmarkResult += runSingle(stopwatch, numberOfRepeats, runFunction);
  }

  for (const auto &benchmark : benchmarks) {
    showBenchmarkResult(benchmark);
  }

  return 0;
}
