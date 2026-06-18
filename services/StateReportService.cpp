#include "services/StateReportService.hpp"

namespace vws
{

    void StateReportService::submit_demo_state_reports(WorldState &world, Tick tick) const
    {
        for (const auto &mission : world.missions())
        {
            VehicleStateReport report;
            report.vehicle_id = mission.vehicle_id;
            report.source_client_id = mission.assigned_client_id;
            report.tick = tick;
            report.position_label = "zone_" + std::to_string(mission.vehicle_id);
            report.speed_mps = 8.0 + static_cast<double>(mission.vehicle_id);
            report.valid = true;

            world.upsert_vehicle_state(report);
        }
    }

} // namespace vws