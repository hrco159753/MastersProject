#pragma once

namespace Em::Core {
template <typename T> class RegisterHandle {
public:
  constexpr RegisterHandle(const std::uintptr_t address) noexcept
      : address{address} {}

  RegisterHandle() = delete;
  RegisterHandle(const RegisterHandle &) = default;
  RegisterHandle(RegisterHandle &&) = default;
  RegisterHandle &operator=(const RegisterHandle &) = default;
  RegisterHandle &operator=(RegisterHandle &&) = default;

  T volatile *ptr() noexcept { return reinterpret_cast<volatile T *>(address); }

  T const volatile *ptr() const noexcept {
    return reinterpret_cast<const volatile T *>(address);
  }

  T volatile &operator*() noexcept { return *ptr(); }

  T const volatile &operator*() const noexcept { return *ptr(); }

private:
  std::uintptr_t address;
};

} // namespace Em::Core