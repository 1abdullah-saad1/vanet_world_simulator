#pragma once

#include "domain/WorldState.hpp"

namespace vws
{

    class TrafficLightService
    {
    public:
        void register_demo_traffic_lights(WorldState &world) const;
    };

} // namespace vws