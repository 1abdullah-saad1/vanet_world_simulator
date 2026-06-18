#include "services/AssignmentService.hpp"

namespace vws
{

    void AssignmentService::assign_demo_missions(WorldState &world) const
    {
        VehicleId next_vehicle_id = 1;

        for (const auto &client : world.clients())
        {
            VehicleMission mission;
            mission.vehicle_id = next_vehicle_id++;
            mission.assigned_client_id = client.id;
            mission.start_point = "start_zone_" + std::to_string(client.id);
            mission.target_point = "target_zone_" + std::to_string(client.id);
            mission.assigned = true;
            world.add_mission(mission);
        }
    }

} // namespace vws