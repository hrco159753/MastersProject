#include <cstdio>

extern "C" {
#include <nrfx_timer.h>
}

#include "Stopwatch.hpp"

namespace Stopwatch {

struct Stopwatch::StopwatchImpl {
  nrfx_timer_t instance;
};

static Stopwatch::StopwatchImpl instance0{.instance = NRFX_TIMER_INSTANCE(0)};

static void handler(nrf_timer_event_t event_type, void *pContext) {
  std::printf("Handler\n");
  if (event_type == NRF_TIMER_EVENT_COMPARE0) {
    static_cast<Stopwatch *>(pContext)->overflowCount++;
  }
}

Stopwatch::Stopwatch() noexcept : overflowCount{0U}, impl{nullptr} {}

bool Stopwatch::init() noexcept {
  const nrfx_timer_config_t config{.frequency = NRF_TIMER_FREQ_16MHz,
                                   .mode = NRF_TIMER_MODE_TIMER,
                                   .bit_width = NRF_TIMER_BIT_WIDTH_32,
                                   .interrupt_priority = 3,
                                   .p_context = static_cast<void *>(this)};

  if (nrfx_timer_init(&instance0.instance, &config, &handler) != NRFX_SUCCESS) {
    return false;
  }
  impl = &instance0;
  nrfx_timer_extended_compare(&impl->instance, NRF_TIMER_CC_CHANNEL0,
                              std::numeric_limits<std::uint32_t>::max(),
                              NRF_TIMER_SHORT_COMPARE0_CLEAR_MASK, true);
  nrfx_timer_enable(&impl->instance);
  return true;
}

void Stopwatch::begin() noexcept {
  overflowCount = 0U;
  nrfx_timer_pause(&impl->instance);
  nrfx_timer_clear(&impl->instance);
  nrfx_timer_resume(&impl->instance);
}

std::chrono::microseconds Stopwatch::time() noexcept {
  const std::uint32_t count{
      nrfx_timer_capture(&impl->instance, NRF_TIMER_CC_CHANNEL1)};
  return std::chrono::microseconds{(overflowCount << 28) + (count >> 4)};
}

Stopwatch::~Stopwatch() noexcept {
  if (impl != nullptr) {
    nrfx_timer_uninit(&impl->instance);
  }
}
} // namespace Stopwatch