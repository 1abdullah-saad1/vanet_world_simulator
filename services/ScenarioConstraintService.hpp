#pragma once

#include "domain/WorldState.hpp"

namespace vws
{

    class ScenarioConstraintService
    {
    public:
        void apply_demo_constraints(WorldState &world) const;
    };

} // namespace vws