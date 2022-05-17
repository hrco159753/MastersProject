#pragma once

#include <chrono>
#include <concepts>
#include <string_view>

#include "PolymorphicStopwatch.hpp"

namespace Benchmark {

    struct BenchmarkDescriptor {
        constexpr BenchmarkDescriptor(const std::string_view name, const std::size_t repeat, void (*const run)()) noexcept
            : name{name}, repeat{repeat}, run{run} {}

        const std::string_view name;
        const std::size_t repeat;
        void (*const run)();
    };

    struct BenchmarkResult {
        std::chrono::microseconds totalTime;
    };

    BenchmarkResult benchmark(PolymorphicStopwatch polymorphicStopwatch, const BenchmarkDescriptor &benchmarkDescriptor) noexcept;
}// namespace Benchmark
