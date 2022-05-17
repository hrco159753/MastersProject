#pragma once

#include <array>
#include <optional>
#include <utility>

#include <em/peripheral/rng/Rng.hpp>

namespace Em::Peripheral {
template <typename... Args>
std::optional<Rng::Driver<Args...>> rng(auto &&...args) noexcept {
  return {Rng::Driver<Args...>{std::forward<decltype(args)>(args)...}};
}
} // namespace Em::Peripheral