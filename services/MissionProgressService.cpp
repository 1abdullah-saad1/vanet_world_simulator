#include "services/MissionProgressService.hpp"

namespace vws
{

    MissionProgressSummary MissionProgressService::evaluate(const WorldState &world) const
    {
        MissionProgressSummary summary;

        for (const auto &mission : world.missions())
        {
            MissionProgressEntry entry;
            entry.vehicle_id = mission.vehicle_id;
            entry.assigned_client_id = mission.assigned_client_id;
            entry.target_point = mission.target_point;

            Tick latest_tick = 0;
            bool has_state = false;

            for (const auto &report : world.vehicle_states())
            {
                if (report.vehicle_id != mission.vehicle_id)
                {
                    continue;
                }

                if (!has_state || report.tick > latest_tick)
                {
                    latest_tick = report.tick;
                    entry.last_position_label = report.position_label;
                    has_state = true;
                }
            }

            entry.has_state = has_state;
            entry.reached_target = has_state && (entry.last_position_label == mission.target_point);

            ++summary.total_missions;
            if (entry.reached_target)
            {
                ++summary.reached_missions;
            }
            else
            {
                ++summary.in_progress_missions;
            }

            summary.entries.push_back(entry);
        }

        return summary;
    }

} // namespace vws