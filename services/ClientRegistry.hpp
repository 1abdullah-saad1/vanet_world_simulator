#pragma once

#include "domain/Client.hpp"
#include "domain/WorldState.hpp"

#include <string>

namespace vws {

class ClientRegistry {
public:
    Client register_client(
        const std::string& name,
        ClientType type
    );

    void register_demo_clients(WorldState& world);

private:
    ClientId next_client_id_ = 1;
};

}  // namespace vws