#pragma once

#include "domain/WorldState.hpp"

namespace vws
{

    struct SpeedPolicySummary
    {
        double max_allowed_speed_mps = 0.0;
        std::size_t checked_reports = 0;
        std::size_t violations = 0;
        bool compliant = true;
    };

    class SpeedPolicyService
    {
    public:
        SpeedPolicySummary evaluate(const WorldState &world, double max_allowed_speed_mps) const;
    };

} // namespace vws