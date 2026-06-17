#include "core/Engine.hpp"

#include <iostream>

namespace vws
{

    Engine::Engine()
        : world_{},
          clock_(10.0),
          total_ticks_(5) {}

    void Engine::run()
    {
        std::cout << "VANET World Simulator started" << std::endl;

        initialize_prototypes();
        initialize_world();

        std::cout << "Prototypes loaded: " << world_.prototype_count() << std::endl;
        std::cout << "World objects loaded: " << world_.object_count() << std::endl;

        for (const auto &object : world_.objects())
        {
            std::cout
                << "Object " << object.id
                << " | " << object_type_to_string(object.type)
                << " | " << object.name
                << " | pos=("
                << object.transform.position.x << ", "
                << object.transform.position.y << ")"
                << " | size=("
                << object.dimensions.length_m << ", "
                << object.dimensions.width_m << ", "
                << object.dimensions.height_m << ")"
                << std::endl;
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
            "Basic Vehicle Prototype");

        world_.add_prototype(
            "street.prototype.basic",
            ObjectType::Street,
            "Basic Street Prototype");

        world_.add_prototype(
            "traffic_light.prototype.basic",
            ObjectType::TrafficLight,
            "Basic Traffic Light Prototype");
    }

    void Engine::initialize_world()
    {
        world_.add_object(
            ObjectType::Vehicle,
            "vehicle_001",
            "vehicle.prototype.basic",
            Transform{Vec2{0.0, 0.0}, 0.0},
            Dimensions{4.5, 1.8, 1.5});

        world_.add_object(
            ObjectType::Street,
            "street_001",
            "street.prototype.basic",
            Transform{Vec2{0.0, 0.0}, 0.0},
            Dimensions{100.0, 7.0, 0.0});

        world_.add_object(
            ObjectType::TrafficLight,
            "traffic_light_001",
            "traffic_light.prototype.basic",
            Transform{Vec2{50.0, 0.0}, 0.0},
            Dimensions{0.5, 0.5, 3.0});
    }

    void Engine::tick(std::uint64_t tick_number)
    {
        std::cout
            << "Tick " << tick_number
            << " | objects=" << world_.object_count()
            << " | prototypes=" << world_.prototype_count()
            << std::endl;
    }

}