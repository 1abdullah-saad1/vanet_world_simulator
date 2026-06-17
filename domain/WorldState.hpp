#pragma once

#include "domain/WorldObject.hpp"
#include "domain/Prototype.hpp"
#include "domain/Vehicle.hpp"

#include <vector>
#include <string>
#include <cstddef>

namespace vws
{

    class WorldState
    {
    public:
        void add_prototype(
            const std::string &prototype_id,
            ObjectType type,
            const std::string &label,
            Dimensions dimensions)
        {
            Prototype prototype;
            prototype.id = prototype_id;
            prototype.type = type;
            prototype.label = label;
            prototype.dimensions = dimensions;
            prototype.active = true;

            prototypes_.push_back(prototype);
        }

        ObjectId add_object(
            ObjectType type,
            const std::string &name,
            const std::string &prototype_id,
            Transform transform)
        {
            WorldObject object;
            object.id = next_id_++;
            object.type = type;
            object.name = name;
            object.prototype_id = prototype_id;
            object.transform = transform;
            object.active = true;

            objects_.push_back(object);

            return object.id;
        }

        void add_vehicle_state(
            ObjectId object_id,
            double speed_mps,
            double acceleration_mps2,
            int lane_id,
            double fuel_percent)
        {
            VehicleState state;
            state.object_id = object_id;
            state.speed_mps = speed_mps;
            state.acceleration_mps2 = acceleration_mps2;
            state.lane_id = lane_id;
            state.fuel_percent = fuel_percent;
            state.active = true;

            vehicle_states_.push_back(state);
        }

        const Prototype *find_prototype(const std::string &prototype_id) const
        {
            for (const auto &prototype : prototypes_)
            {
                if (prototype.id == prototype_id)
                {
                    return &prototype;
                }
            }

            return nullptr;
        }

        const VehicleState *find_vehicle_state(ObjectId object_id) const
        {
            for (const auto &state : vehicle_states_)
            {
                if (state.object_id == object_id)
                {
                    return &state;
                }
            }

            return nullptr;
        }

        std::size_t object_count() const
        {
            return objects_.size();
        }

        std::size_t prototype_count() const
        {
            return prototypes_.size();
        }

        std::size_t vehicle_state_count() const
        {
            return vehicle_states_.size();
        }

        const std::vector<WorldObject> &objects() const
        {
            return objects_;
        }

        std::vector<WorldObject> &objects_mutable()
        {
            return objects_;
        }

        const std::vector<Prototype> &prototypes() const
        {
            return prototypes_;
        }

        const std::vector<VehicleState> &vehicle_states() const
        {
            return vehicle_states_;
        }

    private:
        ObjectId next_id_ = 1;

        std::vector<WorldObject> objects_;
        std::vector<Prototype> prototypes_;
        std::vector<VehicleState> vehicle_states_;
    };

}