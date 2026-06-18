#pragma once

#include "domain/Types.hpp"

#include <string>

namespace vws {

struct VehicleMission {
    VehicleId vehicle_id = 0;
    ClientId assigned_client_id = 0;

    std::string start_point;
    std::string target_point;

    bool assigned = false;
};

}  // namespace vws