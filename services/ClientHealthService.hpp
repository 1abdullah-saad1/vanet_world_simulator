#pragma once

#include "domain/WorldState.hpp"

#include <vector>

namespace vws
{

    struct ClientHealthStatus
    {
        ClientId client_id = 0;
        std::string client_name;
        Tick last_report_tick = 0;
        bool has_report = false;
        bool healthy = false;
    };

    struct ClientHealthSummary
    {
        Tick reference_tick = 0;
        std::size_t healthy_clients = 0;
        std::size_t unhealthy_clients = 0;
        std::vector<ClientHealthStatus> statuses;
    };

    class ClientHealthService
    {
    public:
        ClientHealthSummary evaluate(const WorldState &world, Tick reference_tick, Tick max_staleness_ticks) const;
    };

} // namespace vws