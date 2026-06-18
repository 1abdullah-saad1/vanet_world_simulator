#include "core/Engine.hpp"

#include <iostream>

namespace vws
{

    Engine::Engine()
        : world_{},
          client_registry_{},
                    assignment_service_{},
                    state_report_service_{} {}

    void Engine::run()
    {
                std::cout << "VWS v0.0.3 - Collected Vehicle State Reports\n";
        initialize_clients();
        initialize_missions();
                collect_state_reports();
        print_registered_clients();
        print_assigned_missions();
                print_vehicle_states();
    }

    void Engine::initialize_clients()
    {
        client_registry_.register_demo_clients(world_);
    }

    void Engine::initialize_missions()
    {
        assignment_service_.assign_demo_missions(world_);
    }

    void Engine::collect_state_reports()
    {
        constexpr Tick initial_tick = 1;
        state_report_service_.submit_demo_state_reports(world_, initial_tick);
    }

    void Engine::print_registered_clients() const
    {
        std::cout << "Registered clients: " << world_.client_count() << "\n";

        for (const auto &client : world_.clients())
        {
            std::cout << "- id=" << client.id
                      << ", name=" << client.name
                      << ", type=" << client_type_to_string(client.type)
                      << ", registered=" << (client.registered ? "true" : "false")
                      << ", active=" << (client.active ? "true" : "false")
                      << "\n";
        }
    }

    void Engine::print_assigned_missions() const
    {
        std::cout << "Assigned missions: " << world_.mission_count() << "\n";

        for (const auto &mission : world_.missions())
        {
            std::cout << "- vehicle_id=" << mission.vehicle_id
                      << ", assigned_client_id=" << mission.assigned_client_id
                      << ", start_point=" << mission.start_point
                      << ", target_point=" << mission.target_point
                      << ", assigned=" << (mission.assigned ? "true" : "false")
                      << "\n";
        }
    }

    void Engine::print_vehicle_states() const
    {
        std::cout << "Collected vehicle states: " << world_.vehicle_state_count() << "\n";

        for (const auto &state : world_.vehicle_states())
        {
            std::cout << "- vehicle_id=" << state.vehicle_id
                      << ", source_client_id=" << state.source_client_id
                      << ", tick=" << state.tick
                      << ", position_label=" << state.position_label
                      << ", speed_mps=" << state.speed_mps
                      << ", valid=" << (state.valid ? "true" : "false")
                      << "\n";
        }
    }

} // namespace vws
