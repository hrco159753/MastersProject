#include "Benchmark.hpp"
#include "Warmup.hpp"

namespace Benchmark {
    BenchmarkResult benchmark(PolymorphicStopwatch stopwatch, const BenchmarkDescriptor &benchmarkDescriptor) noexcept {
        BenchmarkResult result{.totalTime = std::chrono::microseconds{}};

        warmup(1'000);

        for (std::size_t i{0}; i < benchmarkDescriptor.repeat; ++i) {
            stopwatch.begin();
            benchmarkDescriptor.run();
            result.totalTime += stopwatch.time();
        }

        return result;
    }
}// namespace Benchmark