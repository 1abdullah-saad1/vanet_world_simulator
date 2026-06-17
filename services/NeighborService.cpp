#include "services/NeighborService.hpp"

#include <cmath>

namespace vws
{

    std::size_t NeighborService::count_neighbors(
        const WorldState &world,
        ObjectId vehicle_id,
        double communication_range_m) const
    {
        const WorldObject *source = world.find_object(vehicle_id);

        if (source == nullptr || source->type != ObjectType::Vehicle)
        {
            return 0;
        }

        const VehicleState *source_state = world.find_vehicle_state(vehicle_id);

        if (source_state == nullptr || !source_state->active)
        {
            return 0;
        }

        std::size_t count = 0;

        for (const auto &other : world.objects())
        {
            if (other.id == vehicle_id)
            {
                continue;
            }

            if (other.type != ObjectType::Vehicle)
            {
                continue;
            }

            const VehicleState *other_state = world.find_vehicle_state(other.id);

            if (other_state == nullptr || !other_state->active)
            {
                continue;
            }

            const double d = distance_m(
                source->transform.position,
                other.transform.position);

            if (d <= communication_range_m)
            {
                ++count;
            }
        }

        return count;
    }

    double NeighborService::distance_m(const Vec2 &a, const Vec2 &b) const
    {
        const double dx = a.x - b.x;
        const double dy = a.y - b.y;

        return std::sqrt((dx * dx) + (dy * dy));
    }

}