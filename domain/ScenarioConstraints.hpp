#pragma once

#include "domain/Types.hpp"

#include <string>

namespace vws
{

    struct ScenarioConstraints
    {
        std::string scenario_name;
        Tick tick_interval_ms = 100;
        double max_allowed_speed_mps = 20.0;
        std::size_t min_required_physical_clients = 2;
        std::size_t target_total_clients = 6;
    };

} // namespace vws