#include "services/PacketLedgerService.hpp"

namespace vws
{

    void PacketLedgerService::generate_demo_packet_events(WorldState &world, Tick tick) const
    {
        std::uint64_t next_packet_id = world.packet_record_count() + 1;

        for (const auto &mission : world.missions())
        {
            PacketRecord uplink;
            uplink.packet_id = next_packet_id++;
            uplink.vehicle_id = mission.vehicle_id;
            uplink.client_id = mission.assigned_client_id;
            uplink.tick = tick;
            uplink.direction = PacketDirection::UplinkToServer;
            uplink.topic = "vehicle_state_update";
            world.add_packet_record(uplink);

            PacketRecord downlink;
            downlink.packet_id = next_packet_id++;
            downlink.vehicle_id = mission.vehicle_id;
            downlink.client_id = mission.assigned_client_id;
            downlink.tick = tick;
            downlink.direction = PacketDirection::DownlinkFromServer;
            downlink.topic = "mission_ack";
            world.add_packet_record(downlink);
        }
    }

    PacketLedgerSummary PacketLedgerService::summarize(const WorldState &world) const
    {
        PacketLedgerSummary summary;

        for (const auto &record : world.packet_records())
        {
            ++summary.total_packets;
            if (record.direction == PacketDirection::UplinkToServer)
            {
                ++summary.uplink_packets;
            }
            else
            {
                ++summary.downlink_packets;
            }
        }

        return summary;
    }

} // namespace vws