#include "services/ClientHealthService.hpp"

namespace vws
{

    ClientHealthSummary ClientHealthService::evaluate(const WorldState &world, Tick reference_tick, Tick max_staleness_ticks) const
    {
        ClientHealthSummary summary;
        summary.reference_tick = reference_tick;

        for (const auto &client : world.clients())
        {
            ClientHealthStatus status;
            status.client_id = client.id;
            status.client_name = client.name;

            Tick latest_tick = 0;
            bool has_report = false;

            for (const auto &report : world.vehicle_states())
            {
                if (report.source_client_id != client.id)
                {
                    continue;
                }

                if (!has_report || report.tick > latest_tick)
                {
                    latest_tick = report.tick;
                    has_report = true;
                }
            }

            status.has_report = has_report;
            status.last_report_tick = latest_tick;

            const bool within_allowed_staleness =
                has_report &&
                (reference_tick >= latest_tick) &&
                ((reference_tick - latest_tick) <= max_staleness_ticks);

            status.healthy = client.active && client.registered && within_allowed_staleness;

            if (status.healthy)
            {
                ++summary.healthy_clients;
            }
            else
            {
                ++summary.unhealthy_clients;
            }

            summary.statuses.push_back(status);
        }

        return summary;
    }

} // namespace vws