#include <Config.hpp>

extern "C" {
void run() {
  for (size_t i{0U}; i < 100; ++i) {
    asm volatile("nop");
  }
}
const char *name() { return "Em"; }

size_t repeat() { return 10'000; }
}