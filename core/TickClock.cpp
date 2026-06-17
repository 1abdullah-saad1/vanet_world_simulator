#include "core/TickClock.hpp"

namespace vanet {

Tick TickClock::current() const {
    return tick;
}

void TickClock::advance() {
    ++tick;
}

}  // namespace vanet
