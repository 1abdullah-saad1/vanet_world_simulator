#pragma once

#include "domain/WorldState.hpp"

namespace vws
{

    class TrafficLightControlService
    {
    public:
        void apply_control_step(WorldState &world, std::uint32_t elapsed_seconds) const;

    private:
        static TrafficLightPhase next_phase(TrafficLightPhase phase);
        static std::uint32_t phase_duration_for(TrafficLightControlMode mode, TrafficLightPhase phase);
    };

} // namespace vws