#pragma once

#include "domain/Types.hpp"

#include <string>

namespace vws {

struct Client {
    ClientId id = 0;
    std::string name;
    ClientType type = ClientType::Unknown;
    bool registered = false;
    bool active = true;
};

}  // namespace vws