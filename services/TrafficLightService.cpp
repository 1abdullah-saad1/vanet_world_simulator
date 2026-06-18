#include "services/TrafficLightService.hpp"

namespace vws
{

    void TrafficLightService::register_demo_traffic_lights(WorldState &world) const
    {
        TrafficLightNode timer_node;
        timer_node.id = 1;
        timer_node.name = "tl_timer_001";
        timer_node.mode = TrafficLightControlMode::TimerBased;
        timer_node.phase = TrafficLightPhase::Green;
        timer_node.phase_seconds_remaining = 25;
        world.add_traffic_light(timer_node);

        TrafficLightNode sensor_node;
        sensor_node.id = 2;
        sensor_node.name = "tl_sensor_001";
        sensor_node.mode = TrafficLightControlMode::SensorBased;
        sensor_node.phase = TrafficLightPhase::Red;
        sensor_node.phase_seconds_remaining = 10;
        world.add_traffic_light(sensor_node);

        TrafficLightNode cloud_node;
        cloud_node.id = 3;
        cloud_node.name = "tl_cloud_001";
        cloud_node.mode = TrafficLightControlMode::CentralCloudControlled;
        cloud_node.phase = TrafficLightPhase::Yellow;
        cloud_node.phase_seconds_remaining = 3;
        world.add_traffic_light(cloud_node);
    }

} // namespace vws