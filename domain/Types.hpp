#pragma once

#include <cstdint>
#include <string>

namespace vws
{

    using ClientId = std::uint64_t;
    using VehicleId = std::uint64_t;
    using Tick = std::uint64_t;

    enum class ClientType
    {
        Unknown,
        PhysicalESP32,
        DockerVirtual,
        LocalProcess
    };

    enum class TrafficLightControlMode
    {
        TimerBased,
        SensorBased,
        CentralCloudControlled
    };

    enum class TrafficLightPhase
    {
        Red,
        Yellow,
        Green
    };

    inline std::string client_type_to_string(ClientType type)
    {
        switch (type)
        {
        case ClientType::PhysicalESP32:
            return "PhysicalESP32";
        case ClientType::DockerVirtual:
            return "DockerVirtual";
        case ClientType::LocalProcess:
            return "LocalProcess";
        default:
            return "Unknown";
        }
    }

    inline std::string traffic_light_mode_to_string(TrafficLightControlMode mode)
    {
        switch (mode)
        {
        case TrafficLightControlMode::TimerBased:
            return "TimerBased";
        case TrafficLightControlMode::SensorBased:
            return "SensorBased";
        case TrafficLightControlMode::CentralCloudControlled:
            return "CentralCloudControlled";
        default:
            return "UnknownMode";
        }
    }

    inline std::string traffic_light_phase_to_string(TrafficLightPhase phase)
    {
        switch (phase)
        {
        case TrafficLightPhase::Red:
            return "Red";
        case TrafficLightPhase::Yellow:
            return "Yellow";
        case TrafficLightPhase::Green:
            return "Green";
        default:
            return "UnknownPhase";
        }
    }

} // namespace vws
