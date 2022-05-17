#pragma once

#include <string_view>

namespace Base {
void run() noexcept;
std::string_view name() noexcept;
std::size_t repeat() noexcept;
} // namespace Base