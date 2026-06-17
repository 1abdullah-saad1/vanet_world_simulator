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

            WorldObject *vehicle_object = world.find_object_mutable(vehicle_state.object_id);

            if (vehicle_object == nullptr)
            {
                continue;
            }

            vehicle_object->transform.position.x += vehicle_state.speed_mps * delta_time_s;

            const WorldObject *street_object = world.find_object(vehicle_state.current_street_id);

            if (street_object == nullptr)
            {
                continue;
            }

            const Prototype *street_prototype = world.find_prototype(street_object->prototype_id);

            if (street_prototype == nullptr)
            {
                continue;
            }

            const double street_length_m = street_prototype->dimensions.length_m;

            if (street_length_m > 0.0 && vehicle_object->transform.position.x > street_length_m)
            {
                vehicle_object->transform.position.x = 0.0;
            }
        }
    }

}