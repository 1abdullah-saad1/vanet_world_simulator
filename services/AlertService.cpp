#include "services/AlertService.hpp"

namespace vws
{

    namespace
    {
        void push_alert(AlertSummary &summary, const std::string &code, AlertSeverity severity, const std::string &message)
        {
            AlertRecord record;
            record.code = code;
            record.severity = severity;
            record.message = message;
            summary.records.push_back(record);
            ++summary.total_alerts;

            if (severity == AlertSeverity::Info)
            {
                ++summary.info_alerts;
                return;
            }

            if (severity == AlertSeverity::Warning)
            {
                ++summary.warning_alerts;
                return;
            }

            ++summary.critical_alerts;
        }
    } // namespace

    AlertSummary AlertService::evaluate(
        const StateValidationSummary &state_validation,
        const SpeedPolicySummary &speed_policy,
        const ClientHealthSummary &client_health,
        const ReadinessStatus &readiness,
        const ExperimentSessionStatus &session_status) const
    {
        AlertSummary summary;

        if (state_validation.invalid_reports > 0)
        {
            push_alert(summary, "STATE_INVALID_REPORTS", AlertSeverity::Critical, "Invalid vehicle state reports detected.");
        }

        if (speed_policy.violations > 0)
        {
            push_alert(summary, "SPEED_POLICY_VIOLATION", AlertSeverity::Warning, "Vehicle speed policy violations detected.");
        }

        if (client_health.unhealthy_clients > 0)
        {
            push_alert(summary, "CLIENT_UNHEALTHY", AlertSeverity::Warning, "One or more clients are unhealthy.");
        }

        if (!readiness.ready)
        {
            push_alert(summary, "READINESS_NOT_MET", AlertSeverity::Warning, "Required physical client count is not met.");
        }

        if (session_status.state == ExperimentSessionState::WaitingForClients)
        {
            push_alert(summary, "SESSION_WAITING", AlertSeverity::Info, "Experiment session is waiting for clients.");
        }

        if (summary.total_alerts == 0)
        {
            push_alert(summary, "SYSTEM_OK", AlertSeverity::Info, "No alerts. System status is healthy.");
        }

        return summary;
    }

} // namespace vws