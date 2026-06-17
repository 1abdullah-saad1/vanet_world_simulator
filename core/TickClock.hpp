#pragma once

#include "domain/Types.hpp"

namespace vanet {

class TickClock {
public:
    Tick current() const;
    void advance();

private:
    Tick tick {0};
};

}  // namespace vanet
