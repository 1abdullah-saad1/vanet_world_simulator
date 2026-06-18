#include "services/TrafficLightControlService.hpp"

namespace vws
{

    void TrafficLightControlService::apply_control_step(WorldState &world, std::uint32_t elapsed_seconds) const
    {
        for (auto &light : world.traffic_lights_mutable())
        {
            if (light.phase_seconds_remaining > elapsed_seconds)
            {
                light.phase_seconds_remaining -= elapsed_seconds;
                continue;
            }

            light.phase = next_phase(light.phase);
            light.phase_seconds_remaining = phase_duration_for(light.mode, light.phase);
        }
    }

    TrafficLightPhase TrafficLightControlService::next_phase(TrafficLightPhase phase)
    {
        switch (phase)
        {
        case TrafficLightPhase::Green:
            return TrafficLightPhase::Yellow;
        case TrafficLightPhase::Yellow:
            return TrafficLightPhase::Red;
        case TrafficLightPhase::Red:
            return TrafficLightPhase::Green;
        default:
            return TrafficLightPhase::Red;
        }
    }

    std::uint32_t TrafficLightControlService::phase_duration_for(TrafficLightControlMode mode, TrafficLightPhase phase)
    {
        switch (mode)
        {
        case TrafficLightControlMode::TimerBased:
            if (phase == TrafficLightPhase::Green)
            {
                return 25;
            }
            if (phase == TrafficLightPhase::Yellow)
            {
                return 3;
            }
            return 30;
        case TrafficLightControlMode::SensorBased:
            if (phase == TrafficLightPhase::Green)
            {
                return 12;
            }
            if (phase == TrafficLightPhase::Yellow)
            {
                return 3;
            }
            return 8;
        case TrafficLightControlMode::CentralCloudControlled:
            if (phase == TrafficLightPhase::Green)
            {
                return 15;
            }
            if (phase == TrafficLightPhase::Yellow)
            {
                return 2;
            }
            return 15;
        default:
            return 10;
        }
    }

} // namespace vws