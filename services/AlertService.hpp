#pragma once

#include "services/ClientHealthService.hpp"
#include "services/ReadinessService.hpp"
#include "services/SessionLifecycleService.hpp"
#include "services/SpeedPolicyService.hpp"
#include "services/StateValidationService.hpp"

#include <string>
#include <vector>

namespace vws
{

    enum class AlertSeverity
    {
        Info,
        Warning,
        Critical
    };

    inline const char *alert_severity_to_string(AlertSeverity severity)
    {
        switch (severity)
        {
        case AlertSeverity::Info:
            return "Info";
        case AlertSeverity::Warning:
            return "Warning";
        case AlertSeverity::Critical:
            return "Critical";
        default:
            return "Unknown";
        }
    }

    struct AlertRecord
    {
        std::string code;
        AlertSeverity severity = AlertSeverity::Info;
        std::string message;
    };

    struct AlertSummary
    {
        std::size_t total_alerts = 0;
        std::size_t info_alerts = 0;
        std::size_t warning_alerts = 0;
        std::size_t critical_alerts = 0;
        std::vector<AlertRecord> records;
    };

    class AlertService
    {
    public:
        AlertSummary evaluate(
            const StateValidationSummary &state_validation,
            const SpeedPolicySummary &speed_policy,
            const ClientHealthSummary &client_health,
            const ReadinessStatus &readiness,
            const ExperimentSessionStatus &session_status) const;
    };

} // namespace vws