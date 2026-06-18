#include "services/StateValidationService.hpp"

namespace vws
{

    StateValidationSummary StateValidationService::validate(const WorldState &world) const
    {
        StateValidationSummary summary;
        summary.total_reports = world.vehicle_state_count();

        for (const auto &report : world.vehicle_states())
        {
            bool source_client_matches_mission = false;

            for (const auto &mission : world.missions())
            {
                if (mission.vehicle_id == report.vehicle_id &&
                    mission.assigned_client_id == report.source_client_id)
                {
                    source_client_matches_mission = true;
                    break;
                }
            }

            const bool report_is_valid =
                report.valid &&
                report.tick > 0 &&
                report.speed_mps >= 0.0 &&
                !report.position_label.empty() &&
                source_client_matches_mission;

            if (report_is_valid)
            {
                ++summary.valid_reports;
            }
            else
            {
                ++summary.invalid_reports;
            }
        }

        summary.all_valid = (summary.invalid_reports == 0);
        return summary;
    }

} // namespace vws