#pragma once

#include "domain/Types.hpp"

namespace vws
{

    struct VehicleState
    {
        ObjectId object_id = 0;

        ObjectId current_street_id = 0;
        int lane_id = 1;

        double speed_mps = 0.0;
        double acceleration_mps2 = 0.0;

        double fuel_percent = 100.0;

        bool active = true;
    };

}