#include "core/Engine.hpp"

#include <iostream>

namespace vws
{

    Engine::Engine()
        : world_{},
          client_registry_{},
          client_health_service_{},
          assignment_service_{},
          experiment_log_service_{},
          mission_progress_service_{},
          speed_policy_service_{},
          packet_ledger_service_{},
          scenario_constraint_service_{},
          session_lifecycle_service_{},
          readiness_service_{},
          state_report_service_{},
          state_validation_service_{},
          traffic_light_control_service_{},
          traffic_light_service_{},
          virtual_client_planner_{},
          client_health_summary_{},
          speed_policy_summary_{},
          mission_progress_summary_{},
          packet_ledger_summary_{},
          state_validation_summary_{},
          readiness_status_{},
          virtual_client_plan_{},
          experiment_session_status_{},
          current_tick_{0},
          total_ticks_{3} {}

    void Engine::run()
    {
        std::cout << "VWS v0.0.16 - Speed Policy Enforcement\n";
        initialize_constraints();
        initialize_clients();
        initialize_missions();
        initialize_traffic_lights();
        run_tick_cycle();
        evaluate_mission_progress();
        validate_state_reports();
        evaluate_speed_policy();
        evaluate_client_health();
        evaluate_readiness();
        plan_virtual_clients();
        evaluate_session_lifecycle();
        log_experiment_snapshot();
        print_scenario_constraints();
        print_registered_clients();
        print_assigned_missions();
        print_mission_progress_summary();
        print_packet_ledger_summary();
        print_vehicle_states();
        print_traffic_lights();
        print_state_validation_summary();
        print_speed_policy_summary();
        print_client_health_summary();
        print_tick_execution_summary();
        print_readiness_status();
        print_virtual_client_plan();
        print_session_status();
    }

    void Engine::initialize_constraints()
    {
        scenario_constraint_service_.apply_demo_constraints(world_);
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

    void Engine::run_tick_cycle()
    {
        for (Tick tick = 1; tick <= total_ticks_; ++tick)
        {
            current_tick_ = tick;
            advance_traffic_light_control();
            collect_state_reports(current_tick_);
            collect_packet_events(current_tick_);
        }
    }

    void Engine::advance_traffic_light_control()
    {
        constexpr std::uint32_t elapsed_seconds = 5;
        traffic_light_control_service_.apply_control_step(world_, elapsed_seconds);
    }

    void Engine::collect_state_reports(Tick tick)
    {
        state_report_service_.submit_demo_state_reports(world_, tick);
    }

    void Engine::collect_packet_events(Tick tick)
    {
        packet_ledger_service_.generate_demo_packet_events(world_, tick);
        packet_ledger_summary_ = packet_ledger_service_.summarize(world_);
    }

    void Engine::evaluate_mission_progress()
    {
        mission_progress_summary_ = mission_progress_service_.evaluate(world_);
    }

    void Engine::validate_state_reports()
    {
        state_validation_summary_ = state_validation_service_.validate(world_);
    }

    void Engine::evaluate_speed_policy()
    {
        const double max_allowed_speed_mps =
            world_.has_constraints() ? world_.constraints().max_allowed_speed_mps : 20.0;
        speed_policy_summary_ = speed_policy_service_.evaluate(world_, max_allowed_speed_mps);
    }

    void Engine::evaluate_client_health()
    {
        const Tick reference_tick = current_tick_;
        constexpr Tick max_staleness_ticks = 1;
        client_health_summary_ = client_health_service_.evaluate(world_, reference_tick, max_staleness_ticks);
    }

    void Engine::evaluate_readiness()
    {
        const std::size_t required_physical_clients =
            world_.has_constraints() ? world_.constraints().min_required_physical_clients : 2;
        readiness_status_ = readiness_service_.evaluate(world_, required_physical_clients);
    }

    void Engine::plan_virtual_clients()
    {
        const std::size_t requested_total_clients =
            world_.has_constraints() ? world_.constraints().target_total_clients : 6;
        virtual_client_plan_ = virtual_client_planner_.build_plan(
            readiness_status_,
            requested_total_clients,
            world_.client_count());
    }

    void Engine::evaluate_session_lifecycle()
    {
        experiment_session_status_ = session_lifecycle_service_.evaluate(
            readiness_status_,
            mission_progress_summary_,
            current_tick_,
            total_ticks_);
    }

    void Engine::log_experiment_snapshot() const
    {
        experiment_log_service_.write_snapshot(
            world_,
            state_validation_summary_,
            readiness_status_,
            virtual_client_plan_,
            "logs/experiment_log.csv");
    }

    void Engine::print_scenario_constraints() const
    {
        if (!world_.has_constraints())
        {
            std::cout << "Scenario constraints: UNSET\n";
            return;
        }

        const auto &constraints = world_.constraints();
        std::cout << "Scenario constraints: " << constraints.scenario_name << "\n";
        std::cout << "- tick_interval_ms=" << constraints.tick_interval_ms << "\n";
        std::cout << "- max_allowed_speed_mps=" << constraints.max_allowed_speed_mps << "\n";
        std::cout << "- min_required_physical_clients=" << constraints.min_required_physical_clients << "\n";
        std::cout << "- target_total_clients=" << constraints.target_total_clients << "\n";
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

    void Engine::print_mission_progress_summary() const
    {
        std::cout << "Mission progress summary\n";
        std::cout << "- total_missions=" << mission_progress_summary_.total_missions << "\n";
        std::cout << "- reached_missions=" << mission_progress_summary_.reached_missions << "\n";
        std::cout << "- in_progress_missions=" << mission_progress_summary_.in_progress_missions << "\n";

        for (const auto &entry : mission_progress_summary_.entries)
        {
            std::cout << "- vehicle_id=" << entry.vehicle_id
                      << ", assigned_client_id=" << entry.assigned_client_id
                      << ", target_point=" << entry.target_point
                      << ", last_position_label=" << entry.last_position_label
                      << ", has_state=" << (entry.has_state ? "true" : "false")
                      << ", reached_target=" << (entry.reached_target ? "true" : "false")
                      << "\n";
        }
    }

    void Engine::print_packet_ledger_summary() const
    {
        std::cout << "Packet ledger summary\n";
        std::cout << "- total_packets=" << packet_ledger_summary_.total_packets << "\n";
        std::cout << "- uplink_packets=" << packet_ledger_summary_.uplink_packets << "\n";
        std::cout << "- downlink_packets=" << packet_ledger_summary_.downlink_packets << "\n";

        for (const auto &record : world_.packet_records())
        {
            std::cout << "- packet_id=" << record.packet_id
                      << ", vehicle_id=" << record.vehicle_id
                      << ", client_id=" << record.client_id
                      << ", tick=" << record.tick
                      << ", direction=" << packet_direction_to_string(record.direction)
                      << ", topic=" << record.topic
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

    void Engine::print_state_validation_summary() const
    {
        std::cout << "State validation: "
                  << (state_validation_summary_.all_valid ? "ALL_VALID" : "HAS_INVALID")
                  << "\n";
        std::cout << "- total_reports=" << state_validation_summary_.total_reports << "\n";
        std::cout << "- valid_reports=" << state_validation_summary_.valid_reports << "\n";
        std::cout << "- invalid_reports=" << state_validation_summary_.invalid_reports << "\n";
    }

    void Engine::print_speed_policy_summary() const
    {
        std::cout << "Speed policy summary\n";
        std::cout << "- max_allowed_speed_mps=" << speed_policy_summary_.max_allowed_speed_mps << "\n";
        std::cout << "- checked_reports=" << speed_policy_summary_.checked_reports << "\n";
        std::cout << "- violations=" << speed_policy_summary_.violations << "\n";
        std::cout << "- compliant=" << (speed_policy_summary_.compliant ? "true" : "false") << "\n";
    }

    void Engine::print_client_health_summary() const
    {
        std::cout << "Client health summary (reference_tick=" << client_health_summary_.reference_tick << ")\n";
        std::cout << "- healthy_clients=" << client_health_summary_.healthy_clients << "\n";
        std::cout << "- unhealthy_clients=" << client_health_summary_.unhealthy_clients << "\n";

        for (const auto &status : client_health_summary_.statuses)
        {
            std::cout << "- client_id=" << status.client_id
                      << ", name=" << status.client_name
                      << ", has_report=" << (status.has_report ? "true" : "false")
                      << ", last_report_tick=" << status.last_report_tick
                      << ", healthy=" << (status.healthy ? "true" : "false")
                      << "\n";
        }
    }

    void Engine::print_tick_execution_summary() const
    {
        std::cout << "Tick execution summary\n";
        std::cout << "- total_ticks_executed=" << current_tick_ << "\n";
        std::cout << "- configured_total_ticks=" << total_ticks_ << "\n";
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

    void Engine::print_session_status() const
    {
        std::cout << "Experiment session status\n";
        std::cout << "- state=" << experiment_session_state_to_string(experiment_session_status_.state) << "\n";
        std::cout << "- current_tick=" << experiment_session_status_.current_tick << "\n";
        std::cout << "- planned_ticks=" << experiment_session_status_.planned_ticks << "\n";
        std::cout << "- readiness_gate_passed="
                  << (experiment_session_status_.readiness_gate_passed ? "true" : "false")
                  << "\n";
        std::cout << "- missions_completed="
                  << (experiment_session_status_.missions_completed ? "true" : "false")
                  << "\n";
    }

} // namespace vws
