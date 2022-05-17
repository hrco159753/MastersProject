#include <stdio.h>

#include <Config.hpp>
#include <nrfx_rng.h>

#define COUNT_OF_NUMBERS (1000U)

static const size_t kCountOfNumbers = COUNT_OF_NUMBERS;

static uint8_t numberBuffer[COUNT_OF_NUMBERS];
static volatile size_t index = 0U;

static void rngHandler(const uint8_t randomNumber) {
  numberBuffer[index] = randomNumber;
  index = index + 1;
}

void run() {

  static const nrfx_rng_config_t config = {.error_correction = false,
                                           .interrupt_priority = 2};

  if (nrfx_rng_init(&config, rngHandler) != NRFX_SUCCESS) {
    printf("Driver can not be obtained!\n");
    return;
  }
  nrfx_rng_start();

  while (index < kCountOfNumbers) {
  }

  nrfx_rng_stop();
  nrfx_rng_uninit();

  size_t sum = 0U;
  for (size_t i = 0U; i < kCountOfNumbers; ++i) {
    sum += numberBuffer[i];
  }

  printf("Sum: %u\n", sum);

  // Needs to be reset!
  index = 0;
}
const char *name() { return "Nrf::Rng"; }

size_t repeat() { return kCountOfNumbers; }
