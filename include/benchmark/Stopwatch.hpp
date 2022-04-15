#pragma once

#include <chrono>
#include <concepts>

namespace Benchmark {

struct Stopwatch {
  /*--- Constructors ---*/
  Stopwatch() = default;
  ~Stopwatch();

  [[nodiscard]] bool init() noexcept;

  void start() noexcept;
  void stop() noexcept;
  void reset() noexcept;

  [[nodiscard]] std::chrono::microseconds getElapsedTime() const noexcept;
};

} // namespace Benchmark
