#pragma once

#include "domain/WorldState.hpp"
#include "domain/Types.hpp"

#include <cstddef>

namespace vws
{

    class NeighborService
    {
    public:
        std::size_t count_neighbors(
            const WorldState &world,
            ObjectId vehicle_id,
            double communication_range_m) const;

    private:
        double distance_m(const Vec2 &a, const Vec2 &b) const;
    };

}