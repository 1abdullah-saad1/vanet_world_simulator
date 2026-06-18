#pragma once

#include "domain/WorldState.hpp"

#include <cstddef>

namespace vws
{

    struct StateValidationSummary
    {
        std::size_t total_reports = 0;
        std::size_t valid_reports = 0;
        std::size_t invalid_reports = 0;
        bool all_valid = false;
    };

    class StateValidationService
    {
    public:
        StateValidationSummary validate(const WorldState &world) const;
    };

} // namespace vws