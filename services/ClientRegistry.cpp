#include "services/ClientRegistry.hpp"

namespace vws {

Client ClientRegistry::register_client(
    const std::string& name,
    ClientType type
) {
    Client client;
    client.id = next_client_id_++;
    client.name = name;
    client.type = type;
    client.registered = true;
    client.active = true;

    return client;
}

void ClientRegistry::register_demo_clients(WorldState& world) {
    world.add_client(register_client("client_esp32_001", ClientType::PhysicalESP32));
    world.add_client(register_client("client_docker_001", ClientType::DockerVirtual));
    world.add_client(register_client("client_local_001", ClientType::LocalProcess));
}

}  // namespace vws