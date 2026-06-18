#pragma once

#include "domain/Types.hpp"

#include <string>

namespace vws
{

    struct VehicleStateReport
    {
        VehicleId vehicle_id = 0;
        ClientId source_client_id = 0;
        Tick tick = 0;

        std::string position_label;
        double speed_mps = 0.0;
        bool valid = false;
    };

} // namespace vws