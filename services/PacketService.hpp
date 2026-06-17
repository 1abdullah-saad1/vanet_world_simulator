#pragma once

#include "domain/Types.hpp"
#include "domain/WorldState.hpp"

namespace vanet {

class PacketService {
public:
    void update(WorldState& worldState, Tick tick) const;
};

}  // namespace vanet
