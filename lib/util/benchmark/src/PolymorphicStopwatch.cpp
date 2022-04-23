#include "PolymorphicStopwatch.hpp"

namespace Benchmark {

    void PolymorphicStopwatch::begin() noexcept {
        return pBegin(pStopwatch);
    }
    std::chrono::microseconds PolymorphicStopwatch::time() noexcept {
        return pTime(pStopwatch);
    }

}// namespace Benchmark