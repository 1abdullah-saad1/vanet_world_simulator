#pragma once

#include "domain/Types.hpp"

#include <string>

namespace vws
{

    struct Prototype
    {
        std::string id;
        ObjectType type = ObjectType::Unknown;
        std::string label;

        Dimensions dimensions;

        bool active = true;
    };

}