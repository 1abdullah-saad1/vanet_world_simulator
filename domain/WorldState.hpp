#pragma once

#include <vector>

#include "domain/Street.hpp"
#include "domain/TrafficLight.hpp"
#include "domain/Vehicle.hpp"

namespace vanet {

struct WorldState {
    std::vector<Vehicle> vehicles;
    std::vector<Street> streets;
    std::vector<TrafficLight> trafficLights;
};

}  // namespace vanet
