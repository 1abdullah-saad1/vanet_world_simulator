#include "core/Engine.hpp"

#include <iostream>

namespace vws
{

    Engine::Engine()
        : world_{},
          clock_(10.0),
          mobility_{},
          neighbors_{},
          total_ticks_(5),
          delta_time_s_(0.1),
          communication_range_m_(30.0) {}

    void Engine::run()
    {
        std::cout << "VANET World Simulator started" << std::endl;

        initialize_prototypes();
        initialize_world();

        std::cout << "Prototypes loaded: " << world_.prototype_count() << std::endl;
        std::cout << "World objects loaded: " << world_.object_count() << std::endl;
        std::cout << "Vehicle states loaded: " << world_.vehicle_state_count() << std::endl;

        for (const auto &object : world_.objects())
        {
            const Prototype *prototype = world_.find_prototype(object.prototype_id);

            Dimensions size{};

            if (prototype != nullptr)
            {
                size = prototype->dimensions;
            }

            std::cout
                << "Object " << object.id
                << " | " << object_type_to_string(object.type)
                << " | " << object.name
                << " | prototype=" << object.prototype_id
                << " | pos=("
                << object.transform.position.x << ", "
                << object.transform.position.y << ")"
                << " | size=("
                << size.length_m << ", "
                << size.width_m << ", "
                << size.height_m << ")"
                << std::endl;

            if (object.type == ObjectType::Vehicle)
            {
                const VehicleState *vehicle_state = world_.find_vehicle_state(object.id);

                if (vehicle_state != nullptr)
                {
                    std::cout
                        << "VehicleState"
                        << " | object=" << vehicle_state->object_id
                        << " | street=" << vehicle_state->current_street_id
                        << " | speed=" << vehicle_state->speed_mps << " m/s"
                        << " | acceleration=" << vehicle_state->acceleration_mps2 << " m/s2"
                        << " | lane=" << vehicle_state->lane_id
                        << " | fuel=" << vehicle_state->fuel_percent << "%"
                        << std::endl;
                }
            }
        }

        for (std::uint64_t i = 0; i < total_ticks_; ++i)
        {
            tick(i);
            clock_.wait_for_next_tick();
        }

        std::cout << "Simulation finished" << std::endl;
    }

    void Engine::initialize_prototypes()
    {
        world_.add_prototype(
            "vehicle.prototype.basic",
            ObjectType::Vehicle,
            "Basic Vehicle Prototype",
            Dimensions{4.5, 1.8, 1.5});

        world_.add_prototype(
            "street.prototype.basic",
            ObjectType::Street,
            "Basic Street Prototype",
            Dimensions{100.0, 7.0, 0.0});

        world_.add_prototype(
            "traffic_light.prototype.basic",
            ObjectType::TrafficLight,
            "Basic Traffic Light Prototype",
            Dimensions{0.5, 0.5, 3.0});
    }

    void Engine::initialize_world()
    {
        const ObjectId street_id = world_.add_object(
            ObjectType::Street,
            "street_001",
            "street.prototype.basic",
            Transform{Vec2{0.0, 0.0}, 0.0});

        const ObjectId vehicle_001 = world_.add_object(
            ObjectType::Vehicle,
            "vehicle_001",
            "vehicle.prototype.basic",
            Transform{Vec2{0.0, 0.0}, 0.0});

        world_.add_vehicle_state(
            vehicle_001,
            street_id,
            1,
            10.0,
            1.0,
            100.0);

        const ObjectId vehicle_002 = world_.add_object(
            ObjectType::Vehicle,
            "vehicle_002",
            "vehicle.prototype.basic",
            Transform{Vec2{5.0, 0.0}, 0.0});

        world_.add_vehicle_state(
            vehicle_002,
            street_id,
            2,
            8.0,
            1.0,
            100.0);

        const ObjectId vehicle_003 = world_.add_object(
            ObjectType::Vehicle,
            "vehicle_003",
            "vehicle.prototype.basic",
            Transform{Vec2{20.0, 0.0}, 0.0});

        world_.add_vehicle_state(
            vehicle_003,
            street_id,
            1,
            5.0,
            1.0,
            100.0);

        world_.add_object(
            ObjectType::TrafficLight,
            "traffic_light_001",
            "traffic_light.prototype.basic",
            Transform{Vec2{50.0, 0.0}, 0.0});
    }

    void Engine::tick(std::uint64_t tick_number)
    {
        mobility_.update(world_, delta_time_s_);

        std::cout
            << "Tick " << tick_number
            << " | objects=" << world_.object_count()
            << " | prototypes=" << world_.prototype_count()
            << " | vehicles=" << world_.vehicle_state_count();

        for (const auto &object : world_.objects())
        {
            if (object.type == ObjectType::Vehicle)
            {
                const VehicleState *vehicle_state = world_.find_vehicle_state(object.id);

                const std::size_t neighbor_count = neighbors_.count_neighbors(
                    world_,
                    object.id,
                    communication_range_m_);

                std::cout
                    << " | " << object.name
                    << " street=";

                if (vehicle_state != nullptr)
                {
                    std::cout
                        << vehicle_state->current_street_id
                        << " lane=" << vehicle_state->lane_id
                        << " x=" << object.transform.position.x
                        << " y=" << object.transform.position.y
                        << " speed=" << vehicle_state->speed_mps
                        << " neighbors=" << neighbor_count;
                }
                else
                {
                    std::cout << "none";
                }
            }
        }

        std::cout << std::endl;
    }
}