#include <cstdio>
#include <numeric>
#include <string_view>

#include <Config.hpp>

#include <em/peripheral/Manager.hpp>

namespace Base {

using Em::Peripheral::Rng::Policy;

constexpr static Policy kModulePolicy{Policy::Interrupt};
constexpr static std::size_t kCountOfNumbers{1'000U};

template <Policy kPolicy>
using Constant = std::integral_constant<Policy, kPolicy>;

void pollingImplementation() noexcept {
  std::optional optionalRngDriver{
      Em::Peripheral::rng<Constant<Policy::Polling>>()};
  if (not optionalRngDriver.has_value()) {
    std::printf("Driver can not be obtained!\n");
    return;
  }
  auto &rngDriver{optionalRngDriver.value()};

  const std::array numbers{rngDriver.get<kCountOfNumbers>()};
  const std::size_t sum{
      std::accumulate(std::cbegin(numbers), std::cend(numbers), std::size_t{})};

  std::printf("Sum: %u\n", sum);
}

void interruptImplementation() noexcept {
  std::optional optionalRngDriver{
      Em::Peripheral::rng<Constant<Policy::Interrupt>>()};
  if (not optionalRngDriver.has_value()) {
    std::printf("Driver can not be obtained!\n");
    return;
  }
  auto &rngDriver{optionalRngDriver.value()};

  constinit static std::array<std::uint8_t, kCountOfNumbers> numbers{};
  auto handler{[index = std::size_t{0U}](const std::uint8_t number) mutable {
    numbers[index++] = number;
    if (index < numbers.size()) {
      return false;
    } else {
      return true;
    }
  }};

  const auto condition{rngDriver.set(handler)};
  condition.waitOn();

  const std::size_t sum{
      std::accumulate(std::cbegin(numbers), std::cend(numbers), std::size_t{})};

  std::printf("Sum: %u\n", sum);
}

template <Policy kPolicy> void implementation();
template <> void implementation<Policy::Polling>() { pollingImplementation(); }
template <> void implementation<Policy::Interrupt>() {
  interruptImplementation();
}

template <Policy kPolicy> constexpr static std::string_view kBenchmarkName;
template <>
constexpr std::string_view kBenchmarkName<Policy::Polling>{"Em::Rng::Polling"};
template <>
constexpr std::string_view kBenchmarkName<Policy::Interrupt>{
    "Em::Rng::Interrupt"};

} // namespace Base

extern "C" {
void run() { Base::implementation<Base::kModulePolicy>(); }

const char *name() { return Base::kBenchmarkName<Base::kModulePolicy>.data(); }

size_t repeat() { return Base::kCountOfNumbers; }
}