#include <cstdio>

#include <Config.hpp>

extern "C" {
#include <nrfx_rng.h>
}

namespace Base {
const static std::size_t kCountOfNumbers{1'000U};

static std::uint8_t numberBuffer[kCountOfNumbers];
static volatile std::size_t index{0U};

static void rngHandler(const std::uint8_t randomNumber) {
  numberBuffer[index] = randomNumber;
  index = index + 1;
}

void run() noexcept {

  const static nrfx_rng_config_t config{.error_correction = false,
                                        .interrupt_priority = 2};

  if (nrfx_rng_init(&config, rngHandler) != NRFX_SUCCESS) {
    std::printf("Driver can not be obtained!\n");
    return;
  }
  nrfx_rng_start();

  while (index < kCountOfNumbers) {
  }

  nrfx_rng_stop();
  nrfx_rng_uninit();

  std::size_t sum{0U};
  for (std::size_t i{0U}; i < kCountOfNumbers; ++i) {
    sum += numberBuffer[i];
  }

  std::printf("Sum: %u\n", sum);

  // Needs to be reset!
  index = 0;
}
std::string_view name() noexcept { return "Nrf::Rng"; }

std::size_t repeat() noexcept { return kCountOfNumbers; }

} // namespace Base