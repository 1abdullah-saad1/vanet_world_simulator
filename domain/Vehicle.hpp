#pragma once

#include "domain/Prototype.hpp"
#include "domain/WorldObject.hpp"

namespace vanet {

class Vehicle : public WorldObject {
public:
    Vehicle(ObjectId objectId = 0, Prototype vehiclePrototype = {})
        : WorldObject(objectId), prototype(vehiclePrototype) {}

    const Prototype& getPrototype() const { return prototype; }

private:
    Prototype prototype;
};

}  // namespace vanet
