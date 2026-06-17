#include "core/TickClock.hpp"

#include <thread>

namespace vws {

TickClock::TickClock(double tick_rate_hz)
    : tick_duration_(1.0 / tick_rate_hz),
      next_tick_time_(std::chrono::steady_clock::now()) {}

void TickClock::wait_for_next_tick() {
    next_tick_time_ += std::chrono::duration_cast<std::chrono::steady_clock::duration>(
        tick_duration_
    );

    std::this_thread::sleep_until(next_tick_time_);
}

}