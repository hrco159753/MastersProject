#include <Config.hpp>

void run() {
  for (size_t i = 0U; i < 100; ++i) {
    __asm__ volatile("nop");
  }
}
const char *name() { return "Nrf"; }

size_t repeat() { return 10000; }
