#pragma once

#include "services/ReadinessService.hpp"

#include <cstddef>

namespace vws
{

    struct VirtualClientPlan
    {
        std::size_t requested_total_clients = 0;
        std::size_t current_registered_clients = 0;
        std::size_t needed_virtual_clients = 0;
        bool should_provision = false;
    };

    class VirtualClientPlanner
    {
    public:
        VirtualClientPlan build_plan(
            const ReadinessStatus &readiness,
            std::size_t requested_total_clients,
            std::size_t current_registered_clients) const;
    };

} // namespace vws