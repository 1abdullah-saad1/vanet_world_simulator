#include "services/MobilityService.hpp"

namespace vws
{

    void MobilityService::update(WorldState &world, double delta_time_s)
    {
        for (auto &vehicle_state : world.vehicle_states_mutable())
        {
            if (!vehicle_state.active)
            {
                continue;
            }

            vehicle_state.speed_mps += vehicle_state.acceleration_mps2 * delta_time_s;

            if (vehicle_state.speed_mps < 0.0)
            {
                vehicle_state.speed_mps = 0.0;
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