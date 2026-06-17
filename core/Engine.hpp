#pragma once

#include "core/TickClock.hpp"
#include "domain/WorldState.hpp"
#include "services/EventService.hpp"
#include "services/MobilityService.hpp"
#include "services/PacketService.hpp"
#include "services/RadioService.hpp"

namespace vanet {

class Engine {
public:
    void step();

private:
    TickClock clock;
    WorldState worldState;
    MobilityService mobilityService;
    EventService eventService;
    RadioService radioService;
    PacketService packetService;
};

}  // namespace vanet
