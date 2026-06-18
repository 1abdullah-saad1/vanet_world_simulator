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

    private:
        std::vector<Client> clients_;
    };

} // namespace vws
