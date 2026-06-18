#include "services/VirtualClientPlanner.hpp"

namespace vws
{

    VirtualClientPlan VirtualClientPlanner::build_plan(
        const ReadinessStatus &readiness,
        std::size_t requested_total_clients,
        std::size_t current_registered_clients) const
    {
        VirtualClientPlan plan;
        plan.requested_total_clients = requested_total_clients;
        plan.current_registered_clients = current_registered_clients;

        if (requested_total_clients > current_registered_clients)
        {
            plan.needed_virtual_clients = requested_total_clients - current_registered_clients;
        }

        // v0.0.6 only plans provisioning; it does not spawn containers yet.
        plan.should_provision = (!readiness.ready) || (plan.needed_virtual_clients > 0);
        return plan;
    }

} // namespace vws