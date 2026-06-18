#include "services/SessionLifecycleService.hpp"

namespace vws
{

    ExperimentSessionStatus SessionLifecycleService::evaluate(
        const ReadinessStatus &readiness,
        const MissionProgressSummary &mission_progress,
        Tick current_tick,
        Tick planned_ticks) const
    {
        ExperimentSessionStatus status;
        status.current_tick = current_tick;
        status.planned_ticks = planned_ticks;
        status.readiness_gate_passed = readiness.ready;
        status.missions_completed =
            (mission_progress.total_missions > 0) &&
            (mission_progress.reached_missions == mission_progress.total_missions);

        if (!status.readiness_gate_passed)
        {
            status.state = ExperimentSessionState::WaitingForClients;
            return status;
        }

        if (status.missions_completed)
        {
            status.state = ExperimentSessionState::Completed;
            return status;
        }

        if (current_tick > 0)
        {
            status.state = ExperimentSessionState::Running;
            return status;
        }

        status.state = ExperimentSessionState::Created;
        return status;
    }

} // namespace vws