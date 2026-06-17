#pragma once

#include "domain/WorldObject.hpp"
#include "domain/Prototype.hpp"

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
            const std::string &label)
        {
            Prototype prototype;
            prototype.id = prototype_id;
            prototype.type = type;
            prototype.label = label;
            prototype.active = true;

            prototypes_.push_back(prototype);
        }

        ObjectId add_object(
            ObjectType type,
            const std::string &name,
            const std::string &prototype_id)
        {
            WorldObject object;
            object.id = next_id_++;
            object.type = type;
            object.name = name;
            object.prototype_id = prototype_id;
            object.active = true;

            objects_.push_back(object);

            return object.id;
        }

        std::size_t object_count() const
        {
            return objects_.size();
        }

        std::size_t prototype_count() const
        {
            return prototypes_.size();
        }

        const std::vector<WorldObject> &objects() const
        {
            return objects_;
        }

        const std::vector<Prototype> &prototypes() const
        {
            return prototypes_;
        }

    private:
        ObjectId next_id_ = 1;

        std::vector<WorldObject> objects_;
        std::vector<Prototype> prototypes_;
    };

}