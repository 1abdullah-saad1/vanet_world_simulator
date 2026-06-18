#pragma once

#include "domain/WorldState.hpp"
#include "services/ReadinessService.hpp"
#include "services/StateValidationService.hpp"
#include "services/VirtualClientPlanner.hpp"

#include <string>

namespace vws
{

    class ExperimentLogService
    {
    public:
        void write_snapshot(
            const WorldState &world,
            const StateValidationSummary &validation,
            const ReadinessStatus &readiness,
            const VirtualClientPlan &virtual_plan,
            const std::string &path) const;
    };

} // namespace vws