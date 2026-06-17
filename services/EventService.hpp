#pragma once

#include "domain/Types.hpp"
#include "domain/WorldState.hpp"

namespace vanet {

class EventService {
public:
    void update(WorldState& worldState, Tick tick) const;
};

}  // namespace vanet
