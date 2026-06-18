#pragma once

#include "domain/Types.hpp"

#include <string>

namespace vws
{

    struct TrafficLightNode
    {
        std::uint64_t id = 0;
        std::string name;
        TrafficLightControlMode mode = TrafficLightControlMode::TimerBased;
        TrafficLightPhase phase = TrafficLightPhase::Red;
        std::uint32_t phase_seconds_remaining = 0;
    };

} // namespace vws