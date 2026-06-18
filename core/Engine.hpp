#pragma once

#include "domain/WorldState.hpp"
#include "services/AssignmentService.hpp"
#include "services/ClientRegistry.hpp"
#include "services/StateReportService.hpp"

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
        void collect_state_reports();
        void print_registered_clients() const;
        void print_assigned_missions() const;
        void print_vehicle_states() const;

    private:
        WorldState world_;
        ClientRegistry client_registry_;
        AssignmentService assignment_service_;
        StateReportService state_report_service_;
    };

} // namespace vws
