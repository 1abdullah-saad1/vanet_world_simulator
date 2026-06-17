#pragma once

#include "domain/Types.hpp"

namespace vanet {

class WorldObject {
public:
    explicit WorldObject(ObjectId objectId = 0) : id(objectId) {}
    virtual ~WorldObject() = default;

    ObjectId getId() const { return id; }

private:
    ObjectId id;
};

}  // namespace vanet
