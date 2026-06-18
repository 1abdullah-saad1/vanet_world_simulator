#pragma once

#include "domain/WorldState.hpp"
#include "services/ClientRegistry.hpp"

namespace vws
{

    class Engine
    {
    public:
        Engine();

        void run();

    private:
        void initialize_clients();
        void print_registered_clients() const;

    private:
        WorldState world_;
        ClientRegistry client_registry_;
    };

} // namespace vws
