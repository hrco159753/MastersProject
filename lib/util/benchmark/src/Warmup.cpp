#include "Warmup.hpp"

namespace Benchmark {
    void warmup(const std::size_t cycles) noexcept {
        for (std::size_t i{0U}; i < cycles; ++i) {
            asm volatile("");
        }
    }
}// namespace Benchmark