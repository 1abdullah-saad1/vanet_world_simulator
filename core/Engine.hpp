#pragma once

#include "domain/WorldState.hpp"
#include "core/TickClock.hpp"

#include <cstdint>

namespace vws
{

    class Engine
    {
    public:
        Engine();

        void run();

    private:
        void initialize_world();
        void tick(std::uint64_t tick_number);

    private:
        WorldState world_;
        TickClock clock_;

        std::uint64_t total_ticks_;
    };

}