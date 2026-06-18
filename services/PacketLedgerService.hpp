#pragma once

#include "domain/WorldState.hpp"

namespace vws
{

    struct PacketLedgerSummary
    {
        std::size_t total_packets = 0;
        std::size_t uplink_packets = 0;
        std::size_t downlink_packets = 0;
    };

    class PacketLedgerService
    {
    public:
        void generate_demo_packet_events(WorldState &world, Tick tick) const;
        PacketLedgerSummary summarize(const WorldState &world) const;
    };

} // namespace vws