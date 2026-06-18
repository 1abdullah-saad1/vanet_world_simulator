#pragma once

#include "services/MissionProgressService.hpp"
#include "services/ReadinessService.hpp"

namespace vws
{

    enum class ExperimentSessionState
    {
        Created,
        WaitingForClients,
        Running,
        Completed
    };

    inline const char *experiment_session_state_to_string(ExperimentSessionState state)
    {
        switch (state)
        {
        case ExperimentSessionState::Created:
            return "Created";
        case ExperimentSessionState::WaitingForClients:
            return "WaitingForClients";
        case ExperimentSessionState::Running:
            return "Running";
        case ExperimentSessionState::Completed:
            return "Completed";
        default:
            return "Unknown";
        }
    }

    struct ExperimentSessionStatus
    {
        ExperimentSessionState state = ExperimentSessionState::Created;
        Tick current_tick = 0;
        Tick planned_ticks = 0;
        bool readiness_gate_passed = false;
        bool missions_completed = false;
    };

    class SessionLifecycleService
    {
    public:
        ExperimentSessionStatus evaluate(
            const ReadinessStatus &readiness,
            const MissionProgressSummary &mission_progress,
            Tick current_tick,
            Tick planned_ticks) const;
    };

} // namespace vws