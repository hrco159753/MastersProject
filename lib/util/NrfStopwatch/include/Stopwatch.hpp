#pragma once

#include <optional>
#include <chrono>

namespace Stopwatch {
struct Stopwatch {
  struct StopwatchImpl;

  Stopwatch() noexcept;
  ~Stopwatch() noexcept;

  bool init() noexcept;
  void begin() noexcept;
  std::chrono::microseconds time() noexcept;

  std::size_t overflowCount;
private:

  StopwatchImpl *impl;
};
} // namespace Stopwatch