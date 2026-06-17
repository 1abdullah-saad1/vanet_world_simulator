#pragma once

#include <cstdint>
#include <string>

namespace vws
{

    using ObjectId = std::uint64_t;

    enum class ObjectType
    {
        Unknown,
        Vehicle,
        Street,
        TrafficLight,
        Building,
        Pedestrian,
        RSU,
        NoiseZone
    };

    struct Vec2
    {
        double x = 0.0;
        double y = 0.0;
    };

    struct Transform
    {
        Vec2 position;
        double heading_rad = 0.0;
    };

    struct Dimensions
    {
        double length_m = 0.0;
        double width_m = 0.0;
        double height_m = 0.0;
    };

    inline std::string object_type_to_string(ObjectType type)
    {
        switch (type)
        {
        case ObjectType::Vehicle:
            return "Vehicle";
        case ObjectType::Street:
            return "Street";
        case ObjectType::TrafficLight:
            return "TrafficLight";
        case ObjectType::Building:
            return "Building";
        case ObjectType::Pedestrian:
            return "Pedestrian";
        case ObjectType::RSU:
            return "RSU";
        case ObjectType::NoiseZone:
            return "NoiseZone";
        default:
            return "Unknown";
        }
    }

}