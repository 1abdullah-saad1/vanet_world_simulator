#pragma once

#include "domain/Types.hpp"
#include "domain/WorldObject.hpp"

namespace vanet {

enum class TrafficLightState {
    Red,
    Yellow,
    Green,
};

class TrafficLight : public WorldObject {
public:
    TrafficLight(ObjectId objectId = 0, TrafficLightState initialState = TrafficLightState::Red)
        : WorldObject(objectId), state(initialState) {}

    TrafficLightState getState() const { return state; }

private:
    TrafficLightState state;
};

}  // namespace vanet
