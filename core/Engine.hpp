#pragma once

#include "domain/WorldState.hpp"
#include "services/AssignmentService.hpp"
#include "services/ClientRegistry.hpp"
#include "services/ReadinessService.hpp"
#include "services/StateReportService.hpp"
#include "services/TrafficLightService.hpp"

namespace vws
{

    class Engine
    {
    public:
        Engine();

        void run();

    private:
        void initialize_clients();
        void initialize_missions();
        void initialize_traffic_lights();
        void collect_state_reports();
        void evaluate_readiness();
        void print_registered_clients() const;
        void print_assigned_missions() const;
        void print_vehicle_states() const;
        void print_traffic_lights() const;
        void print_readiness_status() const;

    private:
        WorldState world_;
        ClientRegistry client_registry_;
        AssignmentService assignment_service_;
        ReadinessService readiness_service_;
        StateReportService state_report_service_;
        TrafficLightService traffic_light_service_;
        ReadinessStatus readiness_status_;
    };

} // namespace vws
