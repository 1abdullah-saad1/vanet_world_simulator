#pragma once

#include "domain/Client.hpp"
#include "domain/VehicleMission.hpp"

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

    private:
        std::vector<Client> clients_;
        std::vector<VehicleMission> missions_;
    };

} // namespace vws
