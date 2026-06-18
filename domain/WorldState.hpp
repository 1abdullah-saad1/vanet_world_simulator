#pragma once

#include "domain/Client.hpp"
#include "domain/VehicleMission.hpp"
#include "domain/VehicleStateReport.hpp"

#include <algorithm>
#include <cstddef>
#include <vector>

namespace vws
{

    class WorldState
    {
    public:
        void add_client(const Client &client)
        {
            clients_.push_back(client);
        }

        std::size_t client_count() const
        {
            return clients_.size();
        }

        const std::vector<Client> &clients() const
        {
            return clients_;
        }

        void add_mission(const VehicleMission &mission)
        {
            missions_.push_back(mission);
        }

        std::size_t mission_count() const
        {
            return missions_.size();
        }

        const std::vector<VehicleMission> &missions() const
        {
            return missions_;
        }

        void upsert_vehicle_state(const VehicleStateReport &report)
        {
            const auto it = std::find_if(
                vehicle_states_.begin(),
                vehicle_states_.end(),
                [&](const VehicleStateReport &state)
                {
                    return state.vehicle_id == report.vehicle_id;
                });

            if (it != vehicle_states_.end())
            {
                *it = report;
                return;
            }

            vehicle_states_.push_back(report);
        }

        std::size_t vehicle_state_count() const
        {
            return vehicle_states_.size();
        }

        const std::vector<VehicleStateReport> &vehicle_states() const
        {
            return vehicle_states_;
        }

    private:
        std::vector<Client> clients_;
        std::vector<VehicleMission> missions_;
        std::vector<VehicleStateReport> vehicle_states_;
    };

} // namespace vws
