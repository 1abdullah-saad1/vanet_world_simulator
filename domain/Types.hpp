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

} // namespace vws
