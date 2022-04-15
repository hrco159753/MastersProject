#include <cstdio>

extern "C" {
#include <nrfx_timer.h>
}

#include "benchmark/Stopwatch.hpp"

constinit inline static nrfx_timer_config_t instanceConfig = {
    .frequency = NRF_TIMER_FREQ_16MHz,
    .mode = NRF_TIMER_MODE_TIMER,
    .bit_width = NRF_TIMER_BIT_WIDTH_32,
    .interrupt_priority = 1,
    .p_context = nullptr};
static nrfx_timer_t instance = NRFX_TIMER_INSTANCE(0);

static constinit std::size_t numberOfOverflows{0UL};
void timerHandler(const nrf_timer_event_t event, void *) noexcept {
  if (event == NRF_TIMER_EVENT_COMPARE1) {
    return;
  }
  ++numberOfOverflows;
}
namespace Benchmark {

bool Stopwatch::init() noexcept {
  instanceConfig.p_context = static_cast<Stopwatch *>(this);
  if (const auto error{
          nrfx_timer_init(&instance, &instanceConfig, timerHandler)};
      error != NRFX_SUCCESS) {
    return false;
  }

  nrfx_timer_extended_compare(&instance, NRF_TIMER_CC_CHANNEL0,
                              std::numeric_limits<std::uint32_t>::max(),
                              NRF_TIMER_SHORT_COMPARE0_CLEAR_MASK, true);

  nrfx_timer_enable(&instance);
  return true;
}

void Stopwatch::start() noexcept { nrfx_timer_resume(&instance); }

void Stopwatch::stop() noexcept { nrfx_timer_pause(&instance); }

void Stopwatch::reset() noexcept {
  nrfx_timer_clear(&instance);
  numberOfOverflows = 0UL;
}

std::chrono::microseconds Stopwatch::getElapsedTime() const noexcept {
  const auto timerElapsedTime{
      nrfx_timer_capture(&instance, NRF_TIMER_CC_CHANNEL1)};

  const std::chrono::microseconds microsecondsOfOverflow{
      (static_cast<std::uint64_t>(numberOfOverflows) *
       static_cast<std::uint64_t>(std::numeric_limits<std::uint32_t>::max() >>
                                  4))};
  const std::chrono::microseconds microsecondsElapsed{
      static_cast<std::uint32_t>(timerElapsedTime) >> 4};

  return microsecondsOfOverflow + microsecondsElapsed;
}

Stopwatch::~Stopwatch() {
  if (nrfx_timer_is_enabled(&instance)) {
    nrfx_timer_disable(&instance);
  }
  numberOfOverflows = 0;
}

} // namespace Benchmark
