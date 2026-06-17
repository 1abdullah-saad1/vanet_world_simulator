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