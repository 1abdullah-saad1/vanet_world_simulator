#include "services/ReadinessService.hpp"

namespace vws
{

    ReadinessStatus ReadinessService::evaluate(const WorldState &world, std::size_t required_physical_clients) const
    {
        std::size_t available_physical_clients = 0;

        for (const auto &client : world.clients())
        {
            if (client.registered && client.active && client.type == ClientType::PhysicalESP32)
            {
                ++available_physical_clients;
            }
        }

        ReadinessStatus status;
        status.required_physical_clients = required_physical_clients;
        status.available_physical_clients = available_physical_clients;
        status.ready = available_physical_clients >= required_physical_clients;
        return status;
    }

} // namespace vws