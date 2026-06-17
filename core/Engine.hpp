#pragma once

#include "domain/WorldState.hpp"
#include "core/TickClock.hpp"
#include "services/MobilityService.hpp"
#include "services/NeighborService.hpp"

#include <cstdint>

namespace vws
{

    class Engine
    {
    public:
        Engine();

        void run();

    private:
        void initialize_prototypes();
        void initialize_world();
        void tick(std::uint64_t tick_number);

    private:
        WorldState world_;
        TickClock clock_;

        MobilityService mobility_;
        NeighborService neighbors_;

        std::uint64_t total_ticks_;
        double delta_time_s_;
        double communication_range_m_;
    };

}