#pragma once

#include "domain/Types.hpp"
#include "domain/WorldObject.hpp"

namespace vanet {

class Street : public WorldObject {
public:
    Street(ObjectId objectId = 0, double streetLength = 0.0)
        : WorldObject(objectId), length(streetLength) {}

    double getLength() const { return length; }

private:
    double length;
};

}  // namespace vanet
