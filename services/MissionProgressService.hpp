#pragma once

#include "domain/WorldState.hpp"

#include <string>
#include <vector>

namespace vws
{

    struct MissionProgressEntry
    {
        VehicleId vehicle_id = 0;
        ClientId assigned_client_id = 0;
        std::string target_point;
        std::string last_position_label;
        bool has_state = false;
        bool reached_target = false;
    };

    struct MissionProgressSummary
    {
        std::size_t total_missions = 0;
        std::size_t reached_missions = 0;
        std::size_t in_progress_missions = 0;
        std::vector<MissionProgressEntry> entries;
    };

    class MissionProgressService
    {
    public:
        MissionProgressSummary evaluate(const WorldState &world) const;
    };

} // namespace vws