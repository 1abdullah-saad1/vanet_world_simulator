#pragma once

#include "domain/WorldState.hpp"

namespace vws
{

    class MobilityService
    {
    public:
        void update(WorldState &world, double delta_time_s);
    };

}