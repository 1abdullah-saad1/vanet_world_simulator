#pragma once

#include "domain/WorldObject.hpp"

#include <vector>
#include <cstddef>

namespace vws
{

    class WorldState
    {
    public:
        ObjectId add_object(ObjectType type, const std::string &name, const std::string &prototype_id)
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

        const std::vector<WorldObject> &objects() const
        {
            return objects_;
        }

    private:
        ObjectId next_id_ = 1;
        std::vector<WorldObject> objects_;
    };

}