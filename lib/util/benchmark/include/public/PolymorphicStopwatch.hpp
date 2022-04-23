#pragma once

#include <memory>
#include <new>
#include <utility>

#include "StopwatchConcept.hpp"

namespace Benchmark {

    struct PolymorphicStopwatch {
        template<Meta::Stopwatch StopwatchType>
        constexpr PolymorphicStopwatch(StopwatchType &stopwatchType) noexcept
            : pStopwatch{&stopwatchType},
              pBegin{[](void *const pContext) noexcept { return static_cast<StopwatchType *>(pContext)->begin(); }},
              pTime{[](void *const pContext) noexcept { return static_cast<StopwatchType *>(pContext)->time(); }} {
        }
        PolymorphicStopwatch(const PolymorphicStopwatch &) = delete;
        PolymorphicStopwatch &operator=(const PolymorphicStopwatch &) = delete;
        constexpr PolymorphicStopwatch(PolymorphicStopwatch &&other) noexcept
            : pStopwatch{std::exchange(other.pStopwatch, nullptr)}, pBegin{std::exchange(other.pBegin, nullptr)}, pTime{std::exchange(other.pTime, nullptr)} {}
        constexpr PolymorphicStopwatch &operator=(PolymorphicStopwatch &&other) noexcept {
            (void) std::construct_at(this, PolymorphicStopwatch(std::move(other)));
            return *this;
        }

        void begin() noexcept;
        std::chrono::microseconds time() noexcept;

    private:
        void *pStopwatch;
        void (*pBegin)(void *pContext) noexcept;
        std::chrono::microseconds (*pTime)(void *pContext) noexcept;
    };

}// namespace Benchmark