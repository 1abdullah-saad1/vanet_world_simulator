#include "core/Engine.hpp"

#include <iostream>

namespace vws
{

    Engine::Engine()
        : world_{},
          client_registry_{},
          assignment_service_{},
          readiness_service_{},
          state_report_service_{},
          traffic_light_service_{},
          virtual_client_planner_{},
          readiness_status_{},
          virtual_client_plan_{} {}

    void Engine::run()
    {
        std::cout << "VWS v0.0.6 - Virtual Client Provisioning Plan\n";
        initialize_clients();
        initialize_missions();
        initialize_traffic_lights();
        collect_state_reports();
        evaluate_readiness();
        plan_virtual_clients();
        print_registered_clients();
        print_assigned_missions();
        print_vehicle_states();
        print_traffic_lights();
        print_readiness_status();
        print_virtual_client_plan();
    }

    void Engine::initialize_clients()
    {
        client_registry_.register_demo_clients(world_);
    }

    void Engine::initialize_missions()
    {
        assignment_service_.assign_demo_missions(world_);
    }

    void Engine::initialize_traffic_lights()
    {
        traffic_light_service_.register_demo_traffic_lights(world_);
    }

    void Engine::collect_state_reports()
    {
        constexpr Tick initial_tick = 1;
        state_report_service_.submit_demo_state_reports(world_, initial_tick);
    }

    void Engine::evaluate_readiness()
    {
        constexpr std::size_t required_physical_clients = 2;
        readiness_status_ = readiness_service_.evaluate(world_, required_physical_clients);
    }

    void Engine::plan_virtual_clients()
    {
        constexpr std::size_t requested_total_clients = 6;
        virtual_client_plan_ = virtual_client_planner_.build_plan(
            readiness_status_,
            requested_total_clients,
            world_.client_count());
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

    void Engine::print_traffic_lights() const
    {
        std::cout << "Managed traffic lights: " << world_.traffic_light_count() << "\n";

        for (const auto &light : world_.traffic_lights())
        {
            std::cout << "- id=" << light.id
                      << ", name=" << light.name
                      << ", mode=" << traffic_light_mode_to_string(light.mode)
                      << ", phase=" << traffic_light_phase_to_string(light.phase)
                      << ", phase_seconds_remaining=" << light.phase_seconds_remaining
                      << "\n";
        }
    }

    void Engine::print_readiness_status() const
    {
        std::cout << "Readiness status: " << (readiness_status_.ready ? "READY" : "NOT_READY") << "\n";
        std::cout << "- required_physical_clients=" << readiness_status_.required_physical_clients << "\n";
        std::cout << "- available_physical_clients=" << readiness_status_.available_physical_clients << "\n";
    }

    void Engine::print_virtual_client_plan() const
    {
        std::cout << "Virtual client plan: "
                  << (virtual_client_plan_.should_provision ? "PROVISION_NEEDED" : "NO_PROVISION")
                  << "\n";
        std::cout << "- requested_total_clients=" << virtual_client_plan_.requested_total_clients << "\n";
        std::cout << "- current_registered_clients=" << virtual_client_plan_.current_registered_clients << "\n";
        std::cout << "- needed_virtual_clients=" << virtual_client_plan_.needed_virtual_clients << "\n";
    }

} // namespace vws
