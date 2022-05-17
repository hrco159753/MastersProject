#include <Config.hpp>

namespace Base {
void run() noexcept {
  for (std::uint32_t i{0U}; i < 100; ++i) {
    asm volatile("nop");
  }
}
std::string_view name() noexcept { return "Nrf"; }

std::size_t repeat() noexcept { return 10'000; }
} // namespace Base