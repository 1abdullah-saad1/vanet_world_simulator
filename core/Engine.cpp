#include "core/Engine.hpp"

#include <iostream>

namespace vws
{

    Engine::Engine()
        : world_{},
          client_registry_{},
          assignment_service_{} {}

    void Engine::run()
    {
        std::cout << "VWS v0.0.2 - Mission Assignment\n";
        initialize_clients();
        initialize_missions();
        print_registered_clients();
        print_assigned_missions();
    }

    void Engine::initialize_clients()
    {
        client_registry_.register_demo_clients(world_);
    }

    void Engine::initialize_missions()
    {
        assignment_service_.assign_demo_missions(world_);
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

} // namespace vws
