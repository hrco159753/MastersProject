#pragma once

#include <cstdint>
#include <variant>

#include <em/core/RegisterHandle.hpp>

namespace Em::Peripheral::Rng {

struct RngLayout {
  constexpr static std::uintptr_t kBaseAddress{0x4000D000};

  constinit inline static Core::RegisterHandle<std::uint32_t> kTaskStart{
      kBaseAddress + 0x000};
  constinit inline static Core::RegisterHandle<std::uint32_t> kTaskStop{
      kBaseAddress + 0x004};
  constinit inline static Core::RegisterHandle<std::uint32_t> kEventsValueReady{
      kBaseAddress + 0x100};
  constinit inline static Core::RegisterHandle<std::uint32_t> kShorts{
      kBaseAddress + 0x200};
  constinit inline static Core::RegisterHandle<std::uint32_t> kInterruptEnable{
      kBaseAddress + 0x304};
  constinit inline static Core::RegisterHandle<std::uint32_t> kInterruptDisable{
      kBaseAddress + 0x308};
  constinit inline static Core::RegisterHandle<std::uint32_t> kConfig{
      kBaseAddress + 0x504};
  constinit inline static Core::RegisterHandle<std::uint32_t> kValue{
      kBaseAddress + 0x508};
};

enum class Policy { Polling, Interrupt };

template <typename kPolicy = std::integral_constant<Policy, Policy::Polling>>
struct Driver {
  /*--- Types ---*/
  struct Task {
    Task() { *RngLayout::kTaskStart = 0x1; }
    ~Task() { *RngLayout::kTaskStop = 0x1; }
  };

  struct ConditionStruct {
    [[gnu::noinline]] [[nodiscard]] constexpr bool isDone() const noexcept {
      return Driver<std::integral_constant<Policy, Policy::Interrupt>>::done;
    }

    [[gnu::noinline]] void waitOn() const noexcept {
      while (not isDone()) {
      }
    }
  };

  /*--- Constructors ---*/
  Driver() noexcept {
    *RngLayout::kShorts = 0x0;
    *RngLayout::kConfig = 0x0;

    if constexpr (kPolicy::value == Policy::Interrupt) {
      *RngLayout::kInterruptEnable = 0x1;
      Driver::done = true;
    } else if constexpr (kPolicy::value == Policy::Polling) {
      *RngLayout::kInterruptDisable = 0x1;
    }
  }

  /*--- Methods ---*/
  template <std::integral T = std::uint8_t>
  [[gnu::noinline]] T get() noexcept requires(kPolicy::value == Policy::Polling) {
    Task task{};
    T returnValue;
    auto byteArray = static_cast<std::uint8_t *>(&returnValue);

    for (std::size_t i{0}; i < sizeof(T); ++i) {
      while (not *RngLayout::kEventsValueReady) {
      }
      *RngLayout::kEventsValueReady = 0x0;
      byteArray[i] = static_cast<std::uint8_t>(*RngLayout::kValue);
    }

    return returnValue;
  }

  template <std::size_t N, std::integral T = std::uint8_t>
  [[gnu::noinline]] std::array<T, N> get() noexcept requires(kPolicy::value == Policy::Polling) {
    Task task{};
    std::array<T, N> returnValue;

    for (T &elem : returnValue) {
      auto byteArray = static_cast<std::uint8_t *>(&elem);

      for (std::size_t i{0}; i < sizeof(T); ++i) {
        while (not *RngLayout::kEventsValueReady) {
        }
        *RngLayout::kEventsValueReady = 0x0;
        byteArray[i] = static_cast<std::uint8_t>(*RngLayout::kValue);
      }
    }

    return returnValue;
  }

  template <std::integral T = std::uint8_t>
  [[gnu::noinline]] ConditionStruct set(std::invocable<T> auto &userHandler) noexcept
      requires(kPolicy::value == Policy::Interrupt) {
    Driver::context = &userHandler;
    Driver::handler = [](void *const context,
                         const std::uint8_t number) -> bool {
      return (*static_cast<std::remove_reference_t<decltype(userHandler)> *>(
          context))(number);
    };
    Driver::done = false;

    *RngLayout::kTaskStart = 0x1;

    return {};
  }

  static void irqHandler() noexcept
      requires(kPolicy::value == Policy::Interrupt) {
    *RngLayout::kEventsValueReady = 0x0;
    // ASSERT(handler != nullptr);
    if (const bool doneGenerating{Driver::handler(
            Driver::context, static_cast<std::uint8_t>(*RngLayout::kValue))};
        doneGenerating) {
      *RngLayout::kTaskStop = 0x1;
      Driver::done = true;
    }
  }

  /*--- Members ---*/
  static inline volatile std::conditional_t<kPolicy::value == Policy::Interrupt,
                                            bool, std::monostate>
      done{};
  static inline std::conditional_t<kPolicy::value == Policy::Interrupt,
                                            void *, std::monostate>
      context{};
  static inline std::conditional_t<kPolicy::value == Policy::Interrupt,
                                            bool (*)(void *, std::uint8_t),
                                            std::monostate>
      handler{nullptr};
};

extern "C" void RNG_IRQHandler() {
  Driver<std::integral_constant<Policy, Policy::Interrupt>>::irqHandler();
}

} // namespace Em::Peripheral::Rng