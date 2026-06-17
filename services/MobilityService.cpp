#include "services/MobilityService.hpp"

namespace vws
{

    void MobilityService::update(WorldState &world, double delta_time_s)
    {
        for (const auto &vehicle_state : world.vehicle_states())
        {
            if (!vehicle_state.active)
            {
                continue;
            }

            for (auto &object : world.objects_mutable())
            {
                if (object.id == vehicle_state.object_id)
                {
                    object.transform.position.x += vehicle_state.speed_mps * delta_time_s;
                    break;
                }
            }
        }
    }

}