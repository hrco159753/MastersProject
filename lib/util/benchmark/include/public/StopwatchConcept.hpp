#pragma once

#include <chrono>
#include <concepts>

namespace Benchmark::Meta {
    template<typename CandidateType>
    concept Stopwatch = requires(CandidateType &c) {
        { c.begin() }
        noexcept->std::same_as<void>;
        { c.time() }
        noexcept->std::same_as<std::chrono::microseconds>;
    };

}// namespace Benchmark::Meta