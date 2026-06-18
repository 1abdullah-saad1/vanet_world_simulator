#pragma once

#include "domain/WorldState.hpp"
#include "services/AssignmentService.hpp"
#include "services/ClientHealthService.hpp"
#include "services/ClientRegistry.hpp"
#include "services/ExperimentLogService.hpp"
#include "services/MissionProgressService.hpp"
#include "services/PacketLedgerService.hpp"
#include "services/ReadinessService.hpp"
#include "services/ScenarioConstraintService.hpp"
#include "services/StateReportService.hpp"
#include "services/StateValidationService.hpp"
#include "services/TrafficLightControlService.hpp"
#include "services/TrafficLightService.hpp"
#include "services/VirtualClientPlanner.hpp"

namespace vws
{

    class Engine
    {
    public:
        Engine();

        void run();

    private:
        void initialize_constraints();
        void initialize_clients();
        void initialize_missions();
        void initialize_traffic_lights();
        void advance_traffic_light_control();
        void collect_state_reports();
        void collect_packet_events();
        void evaluate_mission_progress();
        void validate_state_reports();
        void evaluate_client_health();
        void evaluate_readiness();
        void plan_virtual_clients();
        void log_experiment_snapshot() const;
        void print_registered_clients() const;
        void print_assigned_missions() const;
        void print_mission_progress_summary() const;
        void print_packet_ledger_summary() const;
        void print_scenario_constraints() const;
        void print_vehicle_states() const;
        void print_traffic_lights() const;
        void print_state_validation_summary() const;
        void print_client_health_summary() const;
        void print_readiness_status() const;
        void print_virtual_client_plan() const;

    private:
        WorldState world_;
        ClientRegistry client_registry_;
        ClientHealthService client_health_service_;
        AssignmentService assignment_service_;
        ExperimentLogService experiment_log_service_;
        MissionProgressService mission_progress_service_;
        PacketLedgerService packet_ledger_service_;
        ScenarioConstraintService scenario_constraint_service_;
        ReadinessService readiness_service_;
        StateReportService state_report_service_;
        StateValidationService state_validation_service_;
        TrafficLightControlService traffic_light_control_service_;
        TrafficLightService traffic_light_service_;
        VirtualClientPlanner virtual_client_planner_;
        ClientHealthSummary client_health_summary_;
        MissionProgressSummary mission_progress_summary_;
        PacketLedgerSummary packet_ledger_summary_;
        StateValidationSummary state_validation_summary_;
        ReadinessStatus readiness_status_;
        VirtualClientPlan virtual_client_plan_;
    };

} // namespace vws
