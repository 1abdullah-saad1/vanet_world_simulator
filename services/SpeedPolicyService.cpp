#include "services/SpeedPolicyService.hpp"

namespace vws
{

    SpeedPolicySummary SpeedPolicyService::evaluate(const WorldState &world, double max_allowed_speed_mps) const
    {
        SpeedPolicySummary summary;
        summary.max_allowed_speed_mps = max_allowed_speed_mps;

        for (const auto &state : world.vehicle_states())
        {
            ++summary.checked_reports;
            if (state.speed_mps > max_allowed_speed_mps)
            {
                ++summary.violations;
            }
        }

        summary.compliant = (summary.violations == 0);
        return summary;
    }

} // namespace vws