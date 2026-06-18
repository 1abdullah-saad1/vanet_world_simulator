#include "services/ExperimentLogService.hpp"

#include <fstream>

namespace vws
{

    void ExperimentLogService::write_snapshot(
        const WorldState &world,
        const StateValidationSummary &validation,
        const ReadinessStatus &readiness,
        const VirtualClientPlan &virtual_plan,
        const std::string &path) const
    {
        std::ofstream output(path, std::ios::app);
        if (!output.is_open())
        {
            return;
        }

        if (output.tellp() == 0)
        {
            output << "clients,missions,vehicle_states,traffic_lights,valid_reports,invalid_reports,readiness,needed_virtual_clients\n";
        }

        output << world.client_count() << ","
               << world.mission_count() << ","
               << world.vehicle_state_count() << ","
               << world.traffic_light_count() << ","
               << validation.valid_reports << ","
               << validation.invalid_reports << ","
               << (readiness.ready ? "READY" : "NOT_READY") << ","
               << virtual_plan.needed_virtual_clients << "\n";
    }

} // namespace vws