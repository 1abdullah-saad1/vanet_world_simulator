#pragma once

#include "domain/WorldState.hpp"

#include <cstddef>

namespace vws
{

    struct ReadinessStatus
    {
        std::size_t required_physical_clients = 0;
        std::size_t available_physical_clients = 0;
        bool ready = false;
    };

    class ReadinessService
    {
    public:
        ReadinessStatus evaluate(const WorldState &world, std::size_t required_physical_clients) const;
    };

} // namespace vws