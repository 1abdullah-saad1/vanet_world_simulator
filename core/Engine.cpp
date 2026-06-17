#include "core/Engine.hpp"

namespace vanet {

void Engine::step() {
    mobilityService.update(worldState, clock.current());
    eventService.update(worldState, clock.current());
    radioService.update(worldState, clock.current());
    packetService.update(worldState, clock.current());
    clock.advance();
}

}  // namespace vanet
