#include "services/ScenarioConstraintService.hpp"

namespace vws
{

    void ScenarioConstraintService::apply_demo_constraints(WorldState &world) const
    {
        ScenarioConstraints constraints;
        constraints.scenario_name = "downtown_grid_demo";
        constraints.tick_interval_ms = 100;
        constraints.max_allowed_speed_mps = 16.7;
        constraints.min_required_physical_clients = 2;
        constraints.target_total_clients = 6;
        world.set_constraints(constraints);
    }

} // namespace vws