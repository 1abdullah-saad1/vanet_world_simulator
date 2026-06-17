#pragma once

#include "domain/Types.hpp"

#include <string>

namespace vws
{

    struct WorldObject
    {
        ObjectId id = 0;
        ObjectType type = ObjectType::Unknown;

        std::string name;
        std::string prototype_id;

        Transform transform;
        Dimensions dimensions;

        bool active = true;
    };

}