#include "core/Engine.hpp"

#include <iostream>

namespace vws {

Engine::Engine()
    : world_{},
      clock_(10.0),
      total_ticks_(5) {}

void Engine::run() {
    std::cout << "VANET World Simulator started" << std::endl;

    for (std::uint64_t i = 0; i < total_ticks_; ++i) {
        tick(i);
        clock_.wait_for_next_tick();
    }

    std::cout << "Simulation finished" << std::endl;
}

void Engine::tick(std::uint64_t tick_number) {
    std::cout << "Tick " << tick_number << std::endl;
}

}