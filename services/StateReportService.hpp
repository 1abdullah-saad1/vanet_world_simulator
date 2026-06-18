#pragma once

#include "domain/WorldState.hpp"

namespace vws
{

    class StateReportService
    {
    public:
        void submit_demo_state_reports(WorldState &world, Tick tick) const;
    };

} // namespace vws