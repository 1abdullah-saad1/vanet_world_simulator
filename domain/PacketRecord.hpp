#pragma once

#include "domain/Types.hpp"

#include <string>

namespace vws
{

    enum class PacketDirection
    {
        UplinkToServer,
        DownlinkFromServer
    };

    inline std::string packet_direction_to_string(PacketDirection direction)
    {
        switch (direction)
        {
        case PacketDirection::UplinkToServer:
            return "UplinkToServer";
        case PacketDirection::DownlinkFromServer:
            return "DownlinkFromServer";
        default:
            return "UnknownDirection";
        }
    }

    struct PacketRecord
    {
        std::uint64_t packet_id = 0;
        VehicleId vehicle_id = 0;
        ClientId client_id = 0;
        Tick tick = 0;
        PacketDirection direction = PacketDirection::UplinkToServer;
        std::string topic;
    };

} // namespace vws