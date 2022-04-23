#include <cstdint>
#include <limits>

static constexpr std::uintptr_t kNvicAddresss{0xE000E100};

namespace EM::Detail {

struct NVIC_Type {
  volatile std::uint32_t ISER[8U];
  std::uint32_t RESERVED0[24U];
  volatile std::uint32_t ICER[8U];
  std::uint32_t RESERVED1[24U];
  volatile std::uint32_t ISPR[8U];
  std::uint32_t RESERVED2[24U];
  volatile std::uint32_t ICPR[8U];
  std::uint32_t RESERVED3[24U];
  volatile std::uint32_t IABR[8U];
  std::uint32_t RESERVED4[56U];
  volatile std::uint8_t IP[240U];
  std::uint32_t RESERVED5[644U];
  volatile std::uint32_t STIR;
};

extern "C" void SystemInit() {

  // Enable all interrupts.
  auto &nvic{*reinterpret_cast<NVIC_Type *>(kNvicAddresss)};
  for (auto &enableRegister : nvic.ISER) {
    enableRegister = std::numeric_limits<std::uint32_t>::max();
  }
}

} // namespace EM::Detail
