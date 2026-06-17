#pragma once

#include <chrono>

namespace vws {

    class TickClock {
    public:
        explicit TickClock(double tick_rate_hz);
    
        void wait_for_next_tick();
    
    private:
        std::chrono::duration<double> tick_duration_;
        std::chrono::steady_clock::time_point next_tick_time_;
    };

}